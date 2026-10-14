//
// Created by baptisteluciani on 14/10/2026.
//

#ifndef MOTIONENGINE_KEYFRAMES_H
#define MOTIONENGINE_KEYFRAMES_H
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "core/easing.h"

struct Keyframe {
    int frame;
    float value;
    std::string easing = "linear";
};

class PropertyAnimation {
public:
    float defaultValue = 0.0f;
    std::vector<Keyframe> keyframes;

    void addKeyframe(int frame, float value, const std::string& easing = "linear") {
        keyframes.push_back({frame, value, easing});
        std::sort(keyframes.begin(), keyframes.end(), [](const Keyframe& a, const Keyframe& b) {
            return a.frame < b.frame;
        });
    }

    float getValueAtFrame(int currentFrame) const {
        if (keyframes.empty()) return defaultValue;
        if (currentFrame <= keyframes.front().frame) return keyframes.front().value;
        if (currentFrame >= keyframes.back().frame) return keyframes.back().value;

        // Trouver l'intervalle entre deux keyframes
        for (size_t i = 0; i < keyframes.size() - 1; ++i) {
            const auto& k1 = keyframes[i];
            const auto& k2 = keyframes[i + 1];

            if (currentFrame >= k1.frame && currentFrame <= k2.frame) {
                float progress = static_cast<float>(currentFrame - k1.frame) / static_cast<float>(k2.frame - k1.frame);
                float easedProgress = Easing::interpolate(k2.easing, progress);
                return k1.value + (k2.value - k1.value) * easedProgress;
            }
        }

        return defaultValue;
    }
};
#endif //MOTIONENGINE_KEYFRAMES_H
