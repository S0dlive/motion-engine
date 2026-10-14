//
// Created by baptisteluciani on 14/10/2026.
//

#ifndef MOTION_ENGINE_TIMELINE_H
#define MOTION_ENGINE_TIMELINE_H
#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "core/keyframes.h"

struct ElementTransform {
    PropertyAnimation posX;
    PropertyAnimation posY;
    PropertyAnimation scaleX;
    PropertyAnimation scaleY;
    PropertyAnimation rotation;
    PropertyAnimation opacity;
    PropertyAnimation blur;
};

struct Element {
    std::string id;
    std::string type;

    float width = 100.0f;
    float height = 100.0f;
    float cornerRadius = 0.0f;

    ElementTransform transform;
};

class Timeline {
public:
    int width = 1280;
    int height = 720;
    int fps = 60;
    int totalFrames = 180;

    std::vector<Element> elements;

    static Timeline loadFromJSON(const std::string& filepath);
};
#endif //MOTION_ENGINE_TIMELINE_H
