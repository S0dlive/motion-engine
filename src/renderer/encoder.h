//
// Created by baptisteluciani on 14/10/2026.
//

#ifndef MOTION_ENGINE_ENCODER_H
#define MOTION_ENGINE_ENCODER_H
#pragma once
#include <string>
#include <cstdio>
#include <vector>
#include <cstdint>

class Encoder {
public:
    Encoder(const std::string& outputFile, int width, int height, int fps);
    ~Encoder();

    void writeFrame(const std::vector<uint8_t>& rgbaData);
    void close();

private:
    FILE* ffmpegPipe = nullptr;
    int width;
    int height;
    int fps;
};
#endif //MOTION_ENGINE_ENCODER_H
