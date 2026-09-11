#pragma once

#include "../ATemplateContent.hpp"
#include "../TemplateContentFactory.hpp"

namespace ui {
    class MainInterfaceContent : public ATemplateContent {
        public:
            void renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) override;
    };
}