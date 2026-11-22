#include "ImGUILayer.hpp"
#include <string_view>
#include <types/World.hpp>
#include <vector>
#include "lib/TemplateType.hpp"
#include "TemplateContentFactory.hpp"
#include "imgui.h"
#include "PresetLoader.hpp"

void ui::ImGUILayer::guiFrameCreation() {
    this->_framesTitle.push_back(ui::layoutInterface::editionWindow.title);
    this->_framesTitle.push_back(ui::layoutInterface::infoWindow.title);
    this->_framesTitle.push_back(ui::layoutInterface::mainWindow.title);
    this->_framesTitle.push_back(ui::layoutInterface::timeWindow.title);

    // Recover all frame
    this->_guiFrames.emplace(
        ui::layoutInterface::editionWindow.title,
        frameContent{
            makeTemplateContent(templateType::DEFAULT),
            ui::layoutInterface::editionWindow.position,
            ui::layoutInterface::editionWindow.size,
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        ui::layoutInterface::infoWindow.title,
        frameContent{
            makeTemplateContent(templateType::INFO_INTERFACE),
            ui::layoutInterface::infoWindow.position,
            ui::layoutInterface::infoWindow.size,
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        ui::layoutInterface::mainWindow.title,
        frameContent{
            makeTemplateContent(templateType::MAIN_INTERFACE),
            ui::layoutInterface::mainWindow.position,
            ui::layoutInterface::mainWindow.size,
        ImGuiCond_FirstUseEver
        }
    );
    this->_guiFrames.emplace(
        ui::layoutInterface::timeWindow.title,
        frameContent{
            makeTemplateContent(templateType::TIME_INTERFACE),
            ui::layoutInterface::timeWindow.position,
            ui::layoutInterface::timeWindow.size,
        ImGuiCond_FirstUseEver
        }
    );
}

void ui::ImGUILayer::init(GLFWwindow *window, const common::SpecificDataUI &specificDataUI)
{
    this->_window = window;
    this->_data.specificDataUI = specificDataUI;
    this->_isShutdown = false;

    this->_presets = loadPresets(PRESETS_PATH);
    this->_data.presets = &this->_presets;

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    bool glfw_ok = ImGui_ImplGlfw_InitForOpenGL(window, true);
    bool gl_ok = ImGui_ImplOpenGL3_Init("#version 130");

    this->guiFrameCreation();
}

bool ui::ImGUILayer::filterRender(const std::string_view &title) {
    if (title == ui::layoutInterface::editionWindow.title && !this->_data.isEditMode)
        return false;
    if (title == ui::layoutInterface::infoWindow.title && !this->_data.isInfoActivate)
        return false;
    if (title == ui::layoutInterface::timeWindow.title && !this->_data.isTimeActivate)
        return false;
    return true;
}

void ui::ImGUILayer::renderFrames() {
    for (auto &title : this->_framesTitle) {
        if (!this->filterRender(title))
            continue;
        const auto &content = this->_guiFrames.find(title)->second;
        content.frame->renderWidgets(title, content, this->_data);
    }
}

void ui::ImGUILayer::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->renderFrames();

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