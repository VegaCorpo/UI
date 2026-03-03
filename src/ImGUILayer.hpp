#pragma once

#include <imgui.h>

namespace ui {

class ImGUILayer {
    public:
        ImGUILayer(const float &fps);
        ~ImGUILayer() { this->shutdown(); };

        void beginFrame(float delta_time, float width, float height);

        // Methods to implement after creation of renderer protocol
        /*
        UIRenderData &getFrame();
        UIRenderData &convertToUIRenderData(ImDrawData *drawData);
        */
        void shutdown();

        private:
            float _fps;
    };

} // namespace ui