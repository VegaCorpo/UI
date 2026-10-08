#include "MainInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "FrameContent.hpp"

void ui::MainInterfaceContent::_renderContent([[maybe_unused]] worldData &data) {
    ImGui::Text("Main Interface");
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