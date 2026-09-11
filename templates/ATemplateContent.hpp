#pragma once

#include "ITemplateContent.hpp"

namespace ui {
    class ATemplateContent : public ITemplateContent {
        public:
            ATemplateContent() = default;
            ~ATemplateContent() override = default;
            void renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) override;

        private:
            float _sliderValue = 0.0f;
            int _counter = 0;
    };
}