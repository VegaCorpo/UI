#include "ImGUILayer.hpp"

ui::ImGUILayer::ImGUILayer() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    // Create custom backends
    io.BackendPlatformName = "CustomCore";
    io.BackendRendererName = "CustomRenderer";
}

void ui::ImGUILayer::beginFrame(float delta_time, float width, float height) {
    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = delta_time;
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

