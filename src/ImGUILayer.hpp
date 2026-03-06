#pragma once

#include <imgui.h>

#include "interfaces/ILayer.hpp"

namespace ui {

    class ImGUILayer : public common::ILayer {
        public:
            ImGUILayer();
            ~ImGUILayer() { this->shutdown(); };

            void beginFrame(float delta_time, float width, float height) override;

            common::RenderDataBuffer& getFrame() override;

            common::RenderDataBuffer& convertToUIRenderData(ImDrawData* drawData);

            void shutdown() override;

        private:
            void recoverVertex(ImDrawList& cmdList);
            void recoverIndices(ImDrawList& cmdList, uint32_t vertexOffset);
            void recoverCommands(ImDrawList& cmdList);

            common::RenderDataBuffer _buffer;
    };

} // namespace ui
