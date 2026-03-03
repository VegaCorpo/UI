#include "ImGUILayer.hpp"

bool ui::ImGUILayer::initWithRenderer(void *native_window, void *gl_context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(
        static_cast<SDL_Window*>(native_window),
        gl_context
    );
    ImGui_ImplOpenGL3_Init("#version 450");

    return true;
}

void ui::ImGUILayer::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

// void ui::ImGUILayer::endFrame() {
// }

void ui::ImGUILayer::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}