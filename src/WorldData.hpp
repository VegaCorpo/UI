#pragma once

#include <optional>
#include <algorithm>
#include <map>
#include <string>
#include <queue>

#include "types/BodyPatch.hpp"
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
        std::queue<common::BodyPatch> edits;
    }; // worldData
} // namespace ui
