#pragma once

#include <imgui.h>

#include "ILayer.hpp"

namespace ui {

    class ImGUILayer : public ILayer {
        public:
            ImGUILayer();
            ~ImGUILayer() { this->shutdown(); };

            void beginFrame(float delta_time, float width, float height) override;

            RenderDrawData& getFrame() override;

            RenderDrawData& convertToUIRenderData(ImDrawData* drawData);

            void shutdown() override;

        private:
            void recoverVertex(ImDrawList& cmdList);
            void recoverIndices(ImDrawList& cmdList, uint32_t vertexOffset);
            void recoverCommands(ImDrawList& cmdList);

            RenderDrawData _buffer;
    };

} // namespace ui
