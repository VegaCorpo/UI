#include "ImGUILayer.hpp"
#include <string_view>
#include <types/World.hpp>
#include <vector>
#include "lib/TemplateType.hpp"
#include "TemplateContentFactory.hpp"
#include "imgui.h"
#include "PresetLoader.hpp"
#include "VisibilitySettings.hpp"

#include <optional>

void ui::ImGUILayer::guiFrameCreation() {
    auto add = [this](const auto &window, templateType type, std::optional<bool> defaultVisible) {
        this->_framesTitle.push_back(window.title);
        if (defaultVisible.has_value()) {
            this->_data.windowVisible.emplace(std::string(window.title), *defaultVisible);
        }
        this->_guiFrames.emplace(
            window.title,
            frameContent{
                makeTemplateContent(type),
                window.position,
                window.size,
                ImGuiCond_FirstUseEver
            }
        );
    };

    add(layoutInterface::mainWindow,    templateType::MAIN_INTERFACE, std::nullopt);
    add(layoutInterface::editionWindow, templateType::DEFAULT,        true);
    add(layoutInterface::infoWindow,    templateType::INFO_INTERFACE, true);
    add(layoutInterface::timeWindow,    templateType::TIME_INTERFACE, false);
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
    registerVisibilitySettings(this->_data.windowVisible);
}

bool ui::ImGUILayer::filterRender(const std::string_view &title) {
    const auto it = this->_data.windowVisible.find(title);
    return it == this->_data.windowVisible.end() || it->second;
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