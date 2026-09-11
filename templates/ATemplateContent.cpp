#include "ATemplateContent.hpp"


void ui::ATemplateContent::renderWidgets(const char *windowTitle,
                                ImVec2 position,
                                ImVec2 size,
                                ImGuiCond condition) {
    ImGui::SetNextWindowPos(position, condition);
    ImGui::SetNextWindowSize(size, condition);
    ImGui::Begin(windowTitle);
    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &this->_sliderValue, 0.0f, 1.0f);

    if (ImGui::Button("Button"))
        this->_counter += 1;

    ImGui::SameLine();
    ImGui::Text("counter = %d", this->_counter);
    ImGui::End();
}