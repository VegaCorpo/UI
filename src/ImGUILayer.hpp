#pragma once

#include <imgui.h>
#include <raylib.h>

#include "ILayer.hpp"

namespace ui {

    class ImGUILayer : public ui::ILayer {
        public:
            ImGUILayer();
            ~ImGUILayer() override { if (!this->_isShutdown) { this->shutdown(); } };

            void beginFrame(float delta_time, float width, float height) override;

            common::RenderDataBuffer& getFrame() override;

            common::RenderDataBuffer& convertToUIRenderData(ImDrawData* drawData);

            void shutdown() override;

            // This methods is actually used for Raylib API
            // If you's using another one, change its content according your Render API
            ImTextureID uploadFontTexture(unsigned char *pixels, int width, int height) override;

        private:

            // Convert Methods
            void _recoverVertex(ImDrawList& cmdList);
            void _recoverIndices(ImDrawList& cmdList, uint32_t vertexOffset);
            void _recoverCommands(ImDrawList& cmdList);

            // GUI Interface Methods
            void _setupStyle();
            void _mainMenu();
            
            // Private Attributs
            common::RenderDataBuffer _buffer;
            Texture2D _fontTexture;
            bool _isShutdown;
    };

} // namespace ui
