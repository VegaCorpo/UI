#include "UIEngine.hpp"
#include "ImGUILayer.hpp"

void ui::UIEngine::update(float dt, float w, float h)
{
    if (this->_layer) {
        this->_layer->beginFrame(dt, w, h);
        this->_renderBuffer = this->_layer->getFrame();
    }
}

void ui::UIEngine::setLayer(std::unique_ptr<ui::ILayer> layer)
{
    this->_layer = std::move(layer);
}

template<typename TLayer = ui::ImGUILayer>
void init()
{
    static_assert(std::is_base_of_v<ui::ILayer, TLayer>,
        "TLayer must inherit from ui::ILayer");
    setLayer(std::make_unique<TLayer>());
}
