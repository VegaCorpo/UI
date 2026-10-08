#pragma once

#include "ITemplateContent.hpp"
#include "WorldData.hpp"

namespace ui {
    class BaseTemplateContent : public ITemplateContent {
        public:
            BaseTemplateContent() = default;
            ~BaseTemplateContent() override = default;
            void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) final;

        private:
            virtual void renderContent(worldData &data);
            float _sliderValue = 0.0f;
            int _counter = 0;
    };
}