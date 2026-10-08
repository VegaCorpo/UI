#pragma once

#include "BaseTemplateContent.hpp"
#include "TemplateContentFactory.hpp"

namespace ui {
    class MainInterfaceContent : public BaseTemplateContent {
        public:
            void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) override;
    };
}