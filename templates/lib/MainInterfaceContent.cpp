#include "MainInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"

void ui::MainInterfaceContent::renderWidgets(const std::string &windowTitle,
                                const ImVec2 &position,
                                const ImVec2 &size,
                                ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);
    ImGui::Begin(windowTitle.c_str());
    ImGui::Text("Main Interface");
    ImGui::End();
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::templateType::MAIN_INTERFACE, [] {
                return std::make_unique<ui::MainInterfaceContent>();
            });
        }
    } autoRegister;
}