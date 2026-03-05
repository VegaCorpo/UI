#include "UIEngine.hpp"
#include <memory>
#include "imgui.h"
#include "types/types.hpp"


extern "C++" {

    std::unique_ptr<ui::IUIEngine> get_engine()
    {
        ImGui::DebugLog("Debug from ImGui");
        return std::make_unique<ui::UIEngine>();
    }

    common::ModuleType get_module_type()
    {
        return common::ModuleType::UI;
    }
}
