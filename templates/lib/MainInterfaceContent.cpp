#include <cfloat>
#include "MainInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "FrameContent.hpp"

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

void ui::MainInterfaceContent::_renderMenuTab() {
    if (ImGui::CollapsingHeader("Scene")) {
        ImGui::TextDisabled("TODO");
    }
    if (ImGui::CollapsingHeader("Layout")) {
        ImGui::TextDisabled("TODO");
    }
}

void ui::MainInterfaceContent::_renderHelpTab() {
    ImGui::TextDisabled("Nothing here yet.");
}

void ui::MainInterfaceContent::_renderContent([[maybe_unused]] worldData &data) {
    if (ImGui::BeginTabBar("main_tabs")) {
        if (ImGui::BeginTabItem("File")) {
            this->_renderFileTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Menu")) {
            this->_renderMenuTab();
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