#pragma once

#include <GLFW/glfw3.h>
#include "types/RenderDataBuffer.hpp"

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Init Methods
            virtual void init(GLFWwindow* window) = 0;

            // Render ImGUI Interface
            virtual void render() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;

    };
} // namespace ui
