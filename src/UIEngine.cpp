#include "UIEngine.hpp"
#include "ImGUILayer.hpp"

void ui::UIEngine::init(void* windowHandle)
{
    auto* window = static_cast<GLFWwindow*>(windowHandle);
    auto layer = std::make_unique<ImGUILayer>();
    layer->init(window);
    this->_layer = std::move(layer);
}

void ui::UIEngine::render()
{
    if (this->_layer) {
        this->_layer->render();
    }
}

// TO DELETE LATER
void ui::UIEngine::update(float dt, float w, float h)
{
    (void)dt;
    (void)w;
    (void)h;
}
