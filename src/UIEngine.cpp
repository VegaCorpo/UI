#include "UIEngine.hpp"
#include "ImGUILayer.hpp"

void ui::UIEngine::update(float dt, float w, float h)
{
    if (this->_layer) {
        this->_layer->beginFrame(dt, w, h);
        this->_renderBuffer = this->_layer->getFrame();
    }
}

template<typename TLayer>
void ui::UIEngine::_initWithLayer(common::TextureLoader loader)
{
    static_assert(std::is_base_of_v<ui::ILayer, TLayer>,
        "TLayer must inherit from ui::ILayer");

    auto layer = std::make_unique<TLayer>();
    
    layer->init(loader); 

    this->_setLayer(std::move(layer));
}

void ui::UIEngine::_setLayer(std::unique_ptr<ui::ILayer> layer)
{
    this->_layer = std::move(layer);
}

void ui::UIEngine::init(GLFWwindow* window)
{
    (void)window;
    // Init Layer with ImGUILayer
    // this->_initWithLayer<ImGUILayer>();
}