#include "ImGUILayer.hpp"
#include <vector>
#include "../templates/lib/TemplateType.hpp"
#include "../templates/TemplateContentFactory.hpp"
#include "imgui.h"

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

    // Recover all frame
    this->_context1 = makeTemplateContent(templateType::DEFAULT);
    this->_infos1 = makeTemplateContent(templateType::INFO_INTERFACE);
    this->_mainInterface = makeTemplateContent(templateType::MAIN_INTERFACE);
}

void ui::ImGUILayer::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static const std::array<ImVec2, 2> contextOption {
        ImVec2(210, 645),
        ImVec2(1055, 150)
    };
    static const std::array<ImVec2, 2> infoOption {
        ImVec2(1010,15),
        ImVec2(250, 200)
    };
    static const std::array<ImVec2, 2> mainOption {
        ImVec2(10, 10),
        ImVec2(200, 1000)
    };
    // Render all frames
    this->_context1->renderWidgets("Context 1", contextOption[0], contextOption[1], ImGuiCond_FirstUseEver);
    this->_infos1->renderWidgets("Info 1", infoOption[0], infoOption[1], ImGuiCond_FirstUseEver);
    this->_mainInterface->renderWidgets("Main Interface", mainOption[0], mainOption[1], ImGuiCond_FirstUseEver);

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    if (!drawData) {
        return;
    }

    // All OpenGl flag
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(this->_window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    ImGui_ImplOpenGL3_RenderDrawData(drawData);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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