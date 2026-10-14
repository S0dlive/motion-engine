#include "renderer/encoder.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <csignal>

Encoder::Encoder(const std::string& outputFile, int width, int height, int fps)
    : width(width), height(height), fps(fps) {

#ifndef _WIN32
    std::signal(SIGPIPE, SIG_IGN);
#endif

    std::stringstream cmd;
    cmd << "ffmpeg -y -f rawvideo -vcodec rawvideo"
        << " -s " << width << "x" << height
        << " -pix_fmt rgba"
        << " -r " << fps
        << " -i - -c:v h264 -pix_fmt yuv420p "
        << outputFile << " > ffmpeg_log.txt 2>&1";

    ffmpegPipe = popen(cmd.str().c_str(), "w");
    if (!ffmpegPipe) {
        throw std::runtime_error("Impossible d'ouvrir le pipe FFmpeg !");
    }
}

Encoder::~Encoder() {
    close();
}

void Encoder::writeFrame(const std::vector<uint8_t>& rgbaData) {
    if (!ffmpegPipe) return;

    size_t written = fwrite(rgbaData.data(), 1, rgbaData.size(), ffmpegPipe);
    if (written < rgbaData.size()) {
        std::cerr << "[Encoder] Erreur d'écriture dans le pipe FFmpeg." << std::endl;
    }

    fflush(ffmpegPipe);
}

void Encoder::close() {
    if (ffmpegPipe) {
        pclose(ffmpegPipe);
        ffmpegPipe = nullptr;
    }
}