#include "PresetLoader.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace {

template <typename V>
void readVec3(const nlohmann::json &item, const char *key, V &out)
{
    if (!item.contains(key)) {
        return;
    }
    const auto &arr = item[key];
    if (!arr.is_array() || arr.size() != 3) {
        throw std::runtime_error(std::string(key) + " must be an array of 3 numbers");
    }
    out.x = arr[0].get<double>();
    out.y = arr[1].get<double>();
    out.z = arr[2].get<double>();
}

ui::EntityPreset parsePreset(const nlohmann::json &item)
{
    ui::EntityPreset preset;
    preset.label = item.at("label").get<std::string>();

    if (item.contains("mass")) {
        preset.mass.mantissa = item["mass"].at("mantissa").get<double>();
        preset.mass.exponent = item["mass"].at("exponent").get<int>();
    }
    preset.radius.value = item.value("radius", 0.0);

    readVec3(item, "position", preset.position);
    readVec3(item, "velocity", preset.velocity);
    readVec3(item, "acceleration", preset.acceleration);

    return preset;
}

} // namespace

std::vector<ui::EntityPreset> ui::loadPresets(const std::string &path)
{
    std::vector<EntityPreset> result;

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Presets: cannot open " << path << std::endl;
        return result;
    }

    const auto root = nlohmann::json::parse(file, nullptr, false);
    if (root.is_discarded() || !root.contains("presets") || !root["presets"].is_array()) {
        std::cerr << "Presets: invalid format in " << path << std::endl;
        return result;
    }

    for (const auto &item : root["presets"]) {
        try {
            result.push_back(parsePreset(item));
        } catch (const std::exception &e) {
            std::cerr << "Presets: entry skipped (" << e.what() << ")" << std::endl;
        }
    }
    return result;
}