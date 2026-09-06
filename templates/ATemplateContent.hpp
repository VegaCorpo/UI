#pragma once

#include "ITemplateContent.hpp"

namespace ui {
    class ATemplateContent : public ITemplateContent {
        public:
            ATemplateContent() = default;
            ~ATemplateContent() override = default;
            void renderWidgets(const char *windowTitle) override;

        private:
             float _sliderValue = 0.0f;
            int _counter = 0;
    };
}