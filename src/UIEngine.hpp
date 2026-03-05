#pragma once

#include "interfaces/IUIEngine.hpp"

namespace ui {

    // Core UI engine interface responsible for generating render data.
    class UIEngine : public common::IUIEngine {
        public:
            ~UIEngine() = default;

            // Method to set Layer according the GUI you want to use
            void setLayer(common::ILayer* layer) override { this->_layer = layer; }

            // Update UI frame and convert it for the renderer
            void update(float dt, float w, float h) override;

        private:
            // Internal buffer containing all UI geometry and commands
            common::RenderDataBuffer _renderBuffer;

            // Layer depending on the GUI you want to use
            common::ILayer* _layer = nullptr;
    };

} // namespace ui
