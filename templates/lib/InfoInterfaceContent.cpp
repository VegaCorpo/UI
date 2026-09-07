#include "InfoInterfaceContent.hpp"
#include "../TemplateContentFactory.hpp"
#include "TemplateType.hpp"

void ui::InfoInterfaceContent::renderWidgets(const char *windowTitle) {
    ImGui::Begin(windowTitle);
    ImGui::TextWrapped("Here you will find all usefull information");
    ImGui::End();
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::INFO_INTERFACE, [] {
                return std::make_unique<ui::InfoInterfaceContent>();
            });
        }
    } autoRegister;
}