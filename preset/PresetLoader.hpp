#pragma once

#include <string>
#include <vector>
#include "EntityPreset.hpp"

namespace ui {

    std::vector<EntityPreset> loadPresets(const std::string &path);
} // namespace ui