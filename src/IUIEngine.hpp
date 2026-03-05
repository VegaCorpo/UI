#pragma once

#include "ILayer.hpp"

namespace ui {
    class IUIEngine {
        public:
            virtual ~IUIEngine() = default;

            virtual void setLayer(ILayer *layer) = 0;

            virtual void update(float dt, float w, float h) = 0;
    };
} // namespace ui