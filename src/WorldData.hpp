#pragma once

#include <optional>
#include <algorithm>

#include "types/World.hpp"
#include "EntityPreset.hpp"

namespace ui {

    struct worldData {
        common::SpecificDataUI specificDataUI;
        common::WorldState worldState;
        const std::vector<EntityPreset> *presets = nullptr;
    }; // worldData
} // namespace ui
