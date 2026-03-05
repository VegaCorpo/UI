#pragma once

#include "ILayer.hpp"

namespace ui {
    class IUIEngine {

        public:
            // Destructor
            virtual ~IUIEngine() = default;

            // Method to set Layer according the GUI you want to use
            virtual void setLayer(ILayer *layer) = 0;

            // Update UI frame and convert it for the renderer
            virtual void update(float dt, float w, float h) = 0;
    };
} // namespace ui