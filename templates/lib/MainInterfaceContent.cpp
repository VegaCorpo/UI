#include "MainInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "FrameContent.hpp"

void ui::MainInterfaceContent::renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                [[maybe_unused]] worldData &data) {
    ImGui::SetNextWindowPos(content.position, content.condition);
    ImGui::SetNextWindowSize(content.size, content.condition);
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