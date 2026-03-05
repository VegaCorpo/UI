#pragma once

#include <cstdint>
#include <vector>

#include "ILayer.hpp"

namespace ui {

    // Core UI engine interface responsible for generating render data.
    class UIEngine {
        public:

            ~UIEngine() = default;

            // Method to set Layer according the GUI you want to use
            void setLayer(ILayer *layer) { _layer = layer; }

            void update(float dt, float w, float h);


        private:

            // Internal buffer containing all UI geometry and commands
            RenderDrawData _renderBuffer;

            // Layer depending on the GUI you want to use
            ILayer *_layer = nullptr;
    };

} // namespace ui