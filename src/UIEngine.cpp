#include "UIEngine.hpp"
#include <iostream>
#include <memory>
#include "imgui.h"

extern "C++" {
std::unique_ptr<ui::UIEngine> get_ui_engine()
{
    ImGui::DebugLog("Debug from ImGui");
    std::cout << "Hello from ui engine" << std::endl;
    return std::make_unique<ui::UIEngine>();
}
}
