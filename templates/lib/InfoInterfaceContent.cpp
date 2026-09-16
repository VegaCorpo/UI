#include "InfoInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "imgui.h"

void ui::InfoInterfaceContent::renderWidgets(const std::string &windowTitle,
                                const ImVec2 &position,
                                const ImVec2 &size,
                                ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);
    ImGui::Begin(windowTitle.c_str());
    ImGui::TextWrapped("Here you will find all usefull information");
    ImGui::End();
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::templateType::INFO_INTERFACE, [] {
                return std::make_unique<ui::InfoInterfaceContent>();
            });
        }
    } autoRegister;
}