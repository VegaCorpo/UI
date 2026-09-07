#pragma once
#include "../ATemplateContent.hpp"

namespace ui {
    class InfoInterfaceContent : public ATemplateContent {
    public:
        void renderWidgets(const char *windowTitle) override;
    };
}