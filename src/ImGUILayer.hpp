#pragma once

#include <imgui.h>

#include "ILayer.hpp"

namespace ui {

    class ImGUILayer : public ui::ILayer {
        public:
            ImGUILayer() : _isShutdown(false) {};

            ~ImGUILayer() override { if (!this->_isShutdown) { this->shutdown(); } };

            void init(common::TextureLoader loader) override;

            void beginFrame(float delta_time, float width, float height) override;

            common::RenderDataBuffer& getFrame() override;

            common::RenderDataBuffer& convertToUIRenderData(ImDrawData* drawData);

            void shutdown() override;

            void getFontData(unsigned char** pixels, int* width, int* height) override;

            void setFontTextureID(unsigned int id) override;

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
            bool _isShutdown;
            unsigned int _fontTextureId = 0;
    };

} // namespace ui
