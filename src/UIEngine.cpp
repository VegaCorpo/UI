#include "UIEngine.hpp"
#include <iostream>
#include <memory>
#include "imgui.h"

extern "C++" {

    void ui::UIEngine::update(float dt, float w, float h) {
        if (this->_layer) {
            this->_layer->beginFrame(dt, w, h);
            this->_renderBuffer = this->_layer->getFrame();
        }
    }
    std::unique_ptr<ui::UIEngine> get_ui_engine()
    {
        ImGui::DebugLog("Debug from ImGui");
        return std::make_unique<ui::UIEngine>();
    }
}
