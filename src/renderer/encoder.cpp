//
// Created by baptisteluciani on 14/10/2026.
//

#include "renderer/encoder.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Encoder::Encoder(const std::string& outputFile, int width, int height, int fps)
    : width(width), height(height), fps(fps) {

    std::stringstream cmd;
    cmd << "ffmpeg -y -f rawvideo -vcodec rawvideo"
        << " -s " << width << "x" << height
        << " -pix_fmt rgba"
        << " -r " << fps
        << " -i - -c:v libx264 -pix_fmt yuv420p -preset ultrafast "
        << outputFile << " > /dev/null 2>&1";

    ffmpegPipe = popen(cmd.str().c_str(), "w");
    if (!ffmpegPipe) {
        throw std::runtime_error("Impossible d'ouvrir le pipe FFmpeg !");
    }
}

Encoder::~Encoder() {
    close();
}

void Encoder::writeFrame(const std::vector<uint8_t>& rgbaData) {
    if (ffmpegPipe) {
        fwrite(rgbaData.data(), 1, rgbaData.size(), ffmpegPipe);
    }
}

void Encoder::close() {
    if (ffmpegPipe) {
        pclose(ffmpegPipe);
        ffmpegPipe = nullptr;
    }
}