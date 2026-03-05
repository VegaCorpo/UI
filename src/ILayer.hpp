#pragma once

#include "UIRenderTypes.hpp" // To change after move it in common

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Called each frame to update the UI
            virtual void beginFrame(float deltaTime, float width, float height) = 0;

            // Returns the universal render buffer for the current frame
            virtual RenderDrawData& getFrame() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;
    };
} // namespace ui
