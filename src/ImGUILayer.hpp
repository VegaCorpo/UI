#pragma once

#include <imgui.h>

namespace ui {

class ImGUILayer {
    public:
        ImGUILayer(const float &fps) : _fps(fps) {}
        ~ImGUILayer() = default;

        bool init();
        void beginFrame(float delta_time, float width, float height);

        // Methods to implement after creation of renderer protocol
        /*
        UIRenderData &getFrame();
        UIRenderData &convertToUIRenderData(ImDrawData *drawData);
        */
        void shutdown();

        const float &getFps() { return this->_fps; }
        void setFps(const float &fps) { _fps = fps; }

        private:
            float _fps;
    };

} // namespace ui