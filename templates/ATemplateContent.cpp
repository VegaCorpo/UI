#include "ATemplateContent.hpp"


void ui::ATemplateContent::renderWidgets(const char *windowTitle) {
    ImGui::Begin(windowTitle);
    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &this->_sliderValue, 0.0f, 1.0f);

    if (ImGui::Button("Button"))
        this->_counter += 1;

    ImGui::SameLine();
    ImGui::Text("counter = %d", this->_counter);
    ImGui::End();
}