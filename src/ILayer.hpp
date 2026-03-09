#pragma once

#include "types/RenderDataBuffer.hpp"

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Called each frame to update the UI
            virtual void beginFrame(float deltaTime, float width, float height) = 0;

            // Returns the universal render buffer for the current frame
            virtual common::RenderDataBuffer& getFrame() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;
    };
} // namespace ui
