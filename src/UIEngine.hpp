#pragma once

#include "interfaces/IUIEngine.hpp"
#include "ILayer.hpp"
#include <memory>

namespace ui {

    // Core UI engine interface responsible for generating render data.
    class UIEngine : public common::IUIEngine {
        public:
            ~UIEngine() = default;

            // Method to set Layer according the GUI you want to use
            void setLayer(std::unique_ptr<ui::ILayer> layer);

            // Update UI frame and convert it for the renderer
            void update(float dt, float w, float h) override;

            void init() override;

        private:
            // Internal buffer containing all UI geometry and commands
            common::RenderDataBuffer _renderBuffer;

            // Layer depending on the GUI you want to use
            std::unique_ptr<ui::ILayer> _layer = nullptr;
    };

} // namespace ui
