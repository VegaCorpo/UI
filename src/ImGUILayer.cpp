#include "ImGUILayer.hpp"

bool ui::ImGUILayer::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    // Create custom backends
    io.BackendPlatformName = "CustomCore";
    io.BackendRendererName = "CustomRenderer";

    return true;
}

void ui::ImGUILayer::beginFrame(float delta_time, float width, float height) {
    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = delta_time > 0.0f ? delta_time : 1.0f / getFps();
    io.DisplaySize = ImVec2(width, height);

    ImGui::NewFrame();
}

/*
UIRenderData &ui::ImGUILayer::getFrame() {
    ImGui::Render();
    ImDrawData* drawData = ImGui::GetDrawData();
    return convertToUIRenderData(drawData);
}

UIRenderData &ui::ImGUILayer::convertToUIRenderData(ImDrawData *drawData) {

}

*/

void ui::ImGUILayer::shutdown() {
    ImGui::DestroyContext();
}

