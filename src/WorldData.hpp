#pragma once

#include <optional>
#include <algorithm>

#include "types/World.hpp"

namespace ui {

    struct worldData {
        common::SpecificDataUI specificDataUI;
        common::WorldState worldState;
    }; // worldData
} // namespace ui
