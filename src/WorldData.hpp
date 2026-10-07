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

namespace {
        std::optional<size_t> findEntityIndex(const std::vector<size_t> &ids, size_t entityId) {
        auto it = std::find(ids.begin(), ids.end(), entityId);
        if (it == ids.end()) {
            return std::nullopt;
        }
        return static_cast<size_t>(std::distance(ids.begin(), it));
    }

}