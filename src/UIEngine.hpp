#pragma once

#include "IUIEngine.hpp"

namespace ui {

    // Core UI engine interface responsible for generating render data.
    class UIEngine : public IUIEngine {
        public:

            ~UIEngine() = default;

            // Method to set Layer according the GUI you want to use
            void setLayer(ILayer *layer) override { this->_layer = layer; }

            // Update UI frame and convert it for the renderer
            void update(float dt, float w, float h) override;

        private:

            // Internal buffer containing all UI geometry and commands
            RenderDrawData _renderBuffer;

            // Layer depending on the GUI you want to use
            ILayer *_layer = nullptr;
    };

} // namespace ui