#pragma once

#include "BaseTemplateContent.hpp"
#include "TemplateContentFactory.hpp"

namespace ui {
    class MainInterfaceContent : public BaseTemplateContent {
        public:
            void renderWidgets(const std::string &windowTitle,
                                const ImVec2 &position,
                                const ImVec2 &size,
                                ImGuiCond condition) override;
    };
}