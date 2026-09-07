#include "MainInterfaceContent.hpp"
#include "../TemplateContentFactory.hpp"
#include "TemplateType.hpp"

void ui::MainInterfaceContent::renderWidgets(const char *windowTitle) {
    ImGui::Begin(windowTitle);
    ImGui::Text("Main Interface");
    ImGui::End();
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::MAIN_INTERFACE, [] {
                return std::make_unique<ui::MainInterfaceContent>();
            });
        }
    } autoRegister;
}