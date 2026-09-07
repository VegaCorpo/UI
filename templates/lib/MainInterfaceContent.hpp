#pragma once

#include "../ATemplateContent.hpp"
#include "../TemplateContentFactory.hpp"

namespace ui {
    class MainInterfaceContent : public ATemplateContent {
        public:
            void renderWidgets(const char *windowTitle) override;
    };
}