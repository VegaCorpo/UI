#pragma once

#include "../ATemplateContent.hpp"
#include "../TemplateContentFactory.hpp"

namespace ui {

    class MainInterfaceContent : public ATemplateContent {
        public:
            struct AutoRegister {
                AutoRegister() {
                    ui::registerTemplateContent(ui::MAIN_INTERFACE, [] {
                        return std::make_unique<ui::MainInterfaceContent>();
                    });
                }
            } autoRegister;
            void renderWidgets(const char *windowTitle) override { /* Main interface */ };
    };
}