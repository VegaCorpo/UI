#pragma once

#include "../ATemplateContent.hpp"
#include "TemplateType.hpp"
#include "../TemplateContentFactory.hpp"


namespace ui {
    class InfoInterfaceContent : public ATemplateContent {
        public:
            struct AutoRegister {
                AutoRegister() {
                    ui::registerTemplateContent(ui::INFO_INTERFACE, [] {
                        return std::make_unique<ui::InfoInterfaceContent>();
                    });
                }
            } autoRegister;
            void renderWidgets(const char *windowTitle) override { /* Info interface */ };
    };
}