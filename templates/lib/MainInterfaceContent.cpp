#include "MainInterfaceContent.hpp"
#include "../TemplateContentFactory.hpp"
#include "TemplateType.hpp"

void ui::MainInterfaceContent::renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);
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