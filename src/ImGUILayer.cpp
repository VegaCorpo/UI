#include "ImGUILayer.hpp"
#include <GLFW/glfw3.h>
#include "rlgl.h"

void ui::ImGUILayer::init(GLFWwindow* window)
{
    this->_window = window;
    this->_isShutdown = false;

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    bool glfw_ok = ImGui_ImplGlfw_InitForOpenGL(window, true);
    bool gl_ok = ImGui_ImplOpenGL3_Init("#version 130");
}

void ui::ImGUILayer::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    int renderWidth = static_cast<int>(io.DisplaySize.x);
    int renderHeigth = static_cast<int>(io.DisplaySize.y);

    ImGui::NewFrame();

    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");

    static float f = 0.0f;
    static int counter = 0;

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    if (ImGui::Button("Button")) {
        counter++;
    }

    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::End();

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    if (!drawData) {
        return;
    }

    rlDrawRenderBatchActive();
    rlDisableScissorTest();
    rlDisableDepthTest();
    rlDisableBackfaceCulling();

    glViewport(0, 0, renderWidth, renderHeigth);
    ImGui_ImplOpenGL3_RenderDrawData(drawData);

    rlEnableDepthTest();
    rlEnableBackfaceCulling();
}

void ui::ImGUILayer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    if (ImGui::GetCurrentContext() != nullptr) {
        ImGui::DestroyContext();
    }

    this->_isShutdown = true;
}
