#pragma once

#include <imgui.h>

#include "ILayer.hpp"

namespace ui {

    class ImGUILayer : public ui::ILayer {
        public:
            ImGUILayer();
            ~ImGUILayer() override { this->shutdown(); };

            void beginFrame(float delta_time, float width, float height) override;

            common::RenderDataBuffer& getFrame() override;

            common::RenderDataBuffer& convertToUIRenderData(ImDrawData* drawData);

            void shutdown() override;

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
    };

} // namespace ui
