#pragma once

#include <memory>
#include <imgui.h>

namespace ui {

class ITemplateContent;

    struct frameContent {
        std::unique_ptr<ITemplateContent> frame;
        const ImVec2 position;
        const ImVec2 size;
        const ImGuiCond_ condition;
    }; // frameContent

} // namespace ui