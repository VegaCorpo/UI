#pragma once

#include "ITemplateContent.hpp"

namespace ui {
    class BaseTemplateContent : public ITemplateContent {
        public:
            BaseTemplateContent() = default;
            ~BaseTemplateContent() override = default;
            void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) override;

        private:
            float _sliderValue = 0.0f;
            int _counter = 0;
    };
}