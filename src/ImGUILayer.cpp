#include "ImGUILayer.hpp"
#include <vector>
#include "lib/TemplateType.hpp"
#include "TemplateContentFactory.hpp"
#include "imgui.h"

void ui::ImGUILayer::guiFrameCreation() {
    const std::string contextTitle = "Context 1";
    this->_framesTitle.push_back(contextTitle);
    constexpr std::array<ImVec2, 2> contextContent = {
        ImVec2(210, 645), 
        ImVec2(1055, 150)
    };

    const std::string infoTitle = "Info 1";
    this->_framesTitle.push_back(infoTitle);
    constexpr std::array<ImVec2, 2> infoContent = {
        ImVec2(1010,15),
        ImVec2(250, 200)
    };

    const std::string mainTitle = "Main Interface";
    this->_framesTitle.push_back(mainTitle);
    constexpr std::array<ImVec2, 2> mainContent = {
        ImVec2(10, 10),
        ImVec2(200, 1000)
    };

    // Recover all frame
    this->_guiFrames.emplace(
        contextTitle,
        frameContent{
            makeTemplateContent(templateType::DEFAULT),
            contextContent[0],
            contextContent[1],
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        infoTitle,
        frameContent{
            makeTemplateContent(templateType::INFO_INTERFACE),
            infoContent[0],
            infoContent[1],
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        mainTitle,
        frameContent{
            makeTemplateContent(templateType::MAIN_INTERFACE),
            mainContent[0],
            mainContent[1],
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