#pragma once

#include "imgui.h"
#include "types/RenderDataBuffer.hpp"
#include "interfaces/IUIEngine.hpp"

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Init Methods
            virtual void init(common::TextureLoader loader) = 0;

            // Called each frame to update the UI
            virtual void beginFrame(float deltaTime, float width, float height) = 0;

            // Returns the universal render buffer for the current frame
            virtual common::RenderDataBuffer& getFrame() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;

            // Recover pixels of the font for the Core
            virtual void getFontData(unsigned char** pixels, int* width, int* height) = 0;
            
            // Recover Texture ID created by the renderer
            virtual void setFontTextureID(unsigned int id) = 0;

    };
} // namespace ui
