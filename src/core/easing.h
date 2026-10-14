//
// Created by baptisteluciani on 14/10/2026.
//

#ifndef MOTIONENGINE_EASING_H
#define MOTIONENGINE_EASING_H
#pragma once

#include <cmath>
#include <string>
#include <numbers>

namespace Easing {

    inline float linear(float t) { return t; }

    inline float easeInCubic(float t) { return t * t * t; }

    inline float easeOutCubic(float t) {
        float f = t - 1.0f;
        return f * f * f + 1.0f;
    }

    inline float easeInOutCubic(float t) {
        return t < 0.5f ? 4.0f * t * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
    }

    // Rebond élastique / Spring (idéal pour le motion design moderne)
    inline float spring(float t) {
        if (t <= 0.0f) return 0.0f;
        if (t >= 1.0f) return 1.0f;
        float c4 = (2.0f * std::numbers::pi_v<float>) / 3.0f;
        return std::pow(2.0f, -10.0f * t) * std::sin((t * 10.0f - 0.75f) * c4) + 1.0f;
    }

    inline float interpolate(const std::string& easingType, float t) {
        if (t <= 0.0f) return 0.0f;
        if (t >= 1.0f) return 1.0f;

        if (easingType == "ease_in") return easeInCubic(t);
        if (easingType == "ease_out") return easeOutCubic(t);
        if (easingType == "ease_in_out") return easeInOutCubic(t);
        if (easingType == "spring") return spring(t);

        return linear(t); // Par défaut
    }

}
#endif //MOTIONENGINE_EASING_H
