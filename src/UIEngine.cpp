#include "UIEngine.hpp"
#include "ImGUILayer.hpp"

void ui::UIEngine::init(void* windowHandle, const common::SpecificDataUI &specificDataUI)
{
    auto* window = static_cast<GLFWwindow*>(windowHandle);
    auto layer = std::make_unique<ImGUILayer>();
    layer->init(window, specificDataUI);
    this->_layer = std::move(layer);
}

void ui::UIEngine::render()
{
    if (this->_layer) {
        this->_layer->render();
    }
}

void ui::UIEngine::update(const common::WorldState &worldState)
{
    this->_layer->updateWorldState(worldState);
}
