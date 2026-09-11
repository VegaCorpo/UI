#include "InfoInterfaceContent.hpp"
#include "../TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "imgui.h"

void ui::InfoInterfaceContent::renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);
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