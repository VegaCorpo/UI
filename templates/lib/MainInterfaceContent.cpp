#include <cfloat>
#include "MainInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "FrameContent.hpp"
#include <imgui_internal.h>

void ui::MainInterfaceContent::_renderFileTab() {
    if (ImGui::CollapsingHeader("Project")) {
        const ImVec2 fullWidth(-FLT_MIN, 0.0f);

        ImGui::Spacing();
        if (ImGui::Button("Import", fullWidth)) {
            // TODO: import
        }
        ImGui::Spacing();
        if (ImGui::Button("Export", fullWidth)) {
            // TODO: export
        }
        ImGui::Spacing();
        if (ImGui::Button("Reset", fullWidth)) {
            // TODO: reset
        }
    }
}

void ui::MainInterfaceContent::_renderMenuTab(worldData &data)
{
    ImGui::Spacing();
    // Mode
    ImGui::SeparatorText("Mode");
    ImGui::Checkbox("Edit Mode", &data.isEditMode);
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
    ImGui::TextWrapped("Open editing scene interface and allows adding entities to the scene.");
    ImGui::PopStyleColor();

    // Filter
    ImGui::SeparatorText("Interface Filter");
    for (auto &[title, visible] : data.windowVisible) {
        if (ImGui::Checkbox(title.c_str(), &visible)) {
            ImGui::MarkIniSettingsDirty();
            if (const char *ini = ImGui::GetIO().IniFilename) {
                ImGui::SaveIniSettingsToDisk(ini);
            }
        }
    }

    // Settings
    ImGui::Spacing();
    ImGui::SeparatorText("Settings");

    if (ImGui::CollapsingHeader("Scene")) {
        ImGui::Indent();
        ImGui::TextDisabled("TODO");
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Layout")) {
        ImGui::Indent();
        ImGui::TextDisabled("TODO");
        ImGui::Unindent();
    }
}

void ui::MainInterfaceContent::_renderHelpTab() {
    ImGui::TextDisabled("Nothing here yet.");
}

void ui::MainInterfaceContent::_renderContent(worldData &data) {
    if (ImGui::BeginTabBar("main_tabs")) {
        if (ImGui::BeginTabItem("File")) {
            this->_renderFileTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Menu")) {
            this->_renderMenuTab(data);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Help")) {
            this->_renderHelpTab();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
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