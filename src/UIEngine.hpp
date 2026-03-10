#pragma once

#include "interfaces/IUIEngine.hpp"
#include "ILayer.hpp"
#include <memory>
#include <types/RenderDataBuffer.hpp>

namespace ui {

    // Core UI engine interface responsible for generating render data.
    class UIEngine : public common::IUIEngine {
        public:
            ~UIEngine() = default;

            void init(common::TextureLoader loader) override;
            
            // Update UI frame and convert it for the renderer
            void update(float dt, float w, float h) override;
            
            common::RenderDataBuffer getDataBuffer() override { return this->_renderBuffer; }

            
        private:

            template<typename TLayer>
            void _initWithLayer(common::TextureLoader loader);
            // Method to set Layer according the GUI you want to use
            void _setLayer(std::unique_ptr<ui::ILayer> layer);
            // Internal buffer containing all UI geometry and commands
            common::RenderDataBuffer _renderBuffer;

            // Layer depending on the GUI you want to use
            std::unique_ptr<ui::ILayer> _layer = nullptr;
    };

} // namespace ui
