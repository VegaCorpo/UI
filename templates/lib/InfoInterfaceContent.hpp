#pragma once
#include "BaseTemplateContent.hpp"

namespace ui {
    class InfoInterfaceContent : public BaseTemplateContent {
    public:
        void renderWidgets(const std::string &windowTitle,
                                const ImVec2 &position,
                                const ImVec2 &size,
                                ImGuiCond condition) override;
    };
}