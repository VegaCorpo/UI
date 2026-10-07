#include "BaseTemplateContent.hpp"
#include "FrameContent.hpp"


void ui::BaseTemplateContent::renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                [[maybe_unused]] worldData &data) {
    ImGui::SetNextWindowPos(content.position, content.condition);
    ImGui::SetNextWindowSize(content.size, content.condition);
    ImGui::Begin(windowTitle.c_str());
    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &this->_sliderValue, 0.0f, 1.0f);

    if (ImGui::Button("Button"))
        this->_counter += 1;

    ImGui::SameLine();
    ImGui::Text("counter = %d", this->_counter);
    ImGui::End();
}