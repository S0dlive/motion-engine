//
// Created by baptisteluciani on 14/10/2026.
//

#include "core/timeline.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

static void parseProperty(const json& j, const std::string& propName, PropertyAnimation& prop, float defaultVal) {
    prop.defaultValue = defaultVal;
    if (j.contains(propName)) {
        if (j[propName].is_number()) {
            prop.defaultValue = j[propName].get<float>();
        } else if (j[propName].is_array()) {
            for (const auto& kf : j[propName]) {
                int frame = kf.value("frame", 0);
                float val = kf.value("val", defaultVal);
                std::string easing = kf.value("easing", "linear");
                prop.addKeyframe(frame, val, easing);
            }
        }
    }
}

Timeline Timeline::loadFromJSON(const std::string& filepath) {
    Timeline tl;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filepath);
    }

    json data;
    file >> data;

    tl.width = data.value("width", 1280);
    tl.height = data.value("height", 720);
    tl.fps = data.value("fps", 60);
    tl.totalFrames = data.value("total_frames", 180);

    for (const auto& item : data["elements"]) {
        Element el;
        el.id = item.value("id", "elem");
        el.type = item.value("type", "rect");
        el.width = item.value("width", 100.0f);
        el.height = item.value("height", 100.0f);
        el.cornerRadius = item.value("corner_radius", 0.0f);

        parseProperty(item, "pos_x", el.transform.posX, tl.width / 2.0f);
        parseProperty(item, "pos_y", el.transform.posY, tl.height / 2.0f);
        parseProperty(item, "scale_x", el.transform.scaleX, 1.0f);
        parseProperty(item, "scale_y", el.transform.scaleY, 1.0f);
        parseProperty(item, "rotation", el.transform.rotation, 0.0f);
        parseProperty(item, "opacity", el.transform.opacity, 1.0f);
        parseProperty(item, "blur", el.transform.blur, 0.0f);

        tl.elements.push_back(el);
    }

    return tl;
}