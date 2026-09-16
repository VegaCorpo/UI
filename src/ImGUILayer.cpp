#include "ImGUILayer.hpp"
#include <vector>
#include "lib/TemplateType.hpp"
#include "TemplateContentFactory.hpp"
#include "imgui.h"

void ui::ImGUILayer::guiFrameCreation() {
    this->_framesTitle.push_back(this->CONTEXT_TITLE);
    this->_framesTitle.push_back(this->INFO_TITLE);
    this->_framesTitle.push_back(this->MAIN_TITLE);

    // Recover all frame
    this->_guiFrames.emplace(
        this->CONTEXT_TITLE,
        frameContent{
            makeTemplateContent(templateType::DEFAULT),
            ImGUILayer::CONTEXT_CONTENT[0],
            ImGUILayer::CONTEXT_CONTENT[1],
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        this->INFO_TITLE,
        frameContent{
            makeTemplateContent(templateType::INFO_INTERFACE),
            ImGUILayer::INFO_CONTENT[0],
            ImGUILayer::INFO_CONTENT[1],
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        this->MAIN_TITLE,
        frameContent{
            makeTemplateContent(templateType::MAIN_INTERFACE),
            ImGUILayer::MAIN_CONTENT[0],
            ImGUILayer::MAIN_CONTENT[1],
        ImGuiCond_FirstUseEver
        }
    );
}

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

    this->guiFrameCreation();
}

void ui::ImGUILayer::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render all frames
    for (auto &title : this->_framesTitle) {
        const auto &frameContent = this->_guiFrames.find(title)->second;
        frameContent.frame->renderWidgets(title, frameContent.position, frameContent.size, frameContent.condition);
    }

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