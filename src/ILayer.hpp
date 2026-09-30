#pragma once

#include <GLFW/glfw3.h>
#include "types/World.hpp"
#include "types/RenderDataBuffer.hpp"

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Init Methods
            virtual void init(GLFWwindow* window, const common::SpecificDataUI &dataUI) = 0;

            // Recover Worldstate Data
            virtual void updateWorldState(const common::WorldState &worldState) = 0;

            // Render ImGUI Interface
            virtual void render() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;

    };
} // namespace ui
