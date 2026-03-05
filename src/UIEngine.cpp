#include "UIEngine.hpp"


void ui::UIEngine::update(float dt, float w, float h) {
    if (this->_layer) {
        this->_layer->beginFrame(dt, w, h);
        this->_renderBuffer = this->_layer->getFrame();
    }
}
