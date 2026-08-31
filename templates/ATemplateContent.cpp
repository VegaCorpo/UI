#include "ATemplateContent.hpp"


void ui::ATemplateContent::render(GLFWwindow *window) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

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

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    ImGui_ImplOpenGL3_RenderDrawData(drawData);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}