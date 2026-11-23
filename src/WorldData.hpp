#pragma once

#include <optional>
#include <algorithm>
#include <map>
#include <string>

#include "types/World.hpp"
#include "EntityPreset.hpp"

namespace ui {

    using VisibilityMap = std::map<std::string, bool, std::less<>>;

    struct worldData {
        common::SpecificDataUI specificDataUI;
        common::WorldState worldState;
        const std::vector<EntityPreset> *presets = nullptr;
        bool isEditMode = true;
        bool isInfoActivate = true;
        bool isTimeActivate = false;
        VisibilityMap windowVisible;
    }; // worldData
} // namespace ui
