#pragma once

#include <cstdio>
#include <string>

#include "types/EntitySpawnRequest.hpp"
#include "components/acceleration.hpp"
#include "components/mass.hpp"
#include "components/orientation.hpp"
#include "components/position.hpp"
#include "components/radius.hpp"
#include "components/velocity.hpp"

namespace ui {

struct EntityPreset {
    std::string label;
    common::components::Mass mass{};
    common::components::Radius radius{};
    common::components::Position position{};
    common::components::Velocity velocity{};
    common::components::Acceleration acceleration{};
    common::components::Orientation orientation{};
};

inline common::EntitySpawnRequest makeSpawnRequest(const EntityPreset &preset)
{
    common::EntitySpawnRequest request{};

    std::snprintf(request.name.value, sizeof(request.name.value), "%s", preset.label.c_str());
    request.mass         = preset.mass;
    request.radius       = preset.radius;
    request.position     = preset.position;
    request.velocity     = preset.velocity;
    request.acceleration = preset.acceleration;
    request.orientation  = preset.orientation;

    return request;
}

} // namespace ui