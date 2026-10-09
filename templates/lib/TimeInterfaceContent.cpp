#include "TimeInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "FrameContent.hpp"

void ui::TimeInterfaceContent::_renderContent([[maybe_unused]] worldData &data) {
    ImGui::TextUnformatted("Time scale");
    ImGui::Separator();

    // Les boutons se partagent équitablement la largeur disponible
    const float spacing = ImGui::GetStyle().ItemSpacing.x;
    const float count = static_cast<float>(SCALES.size());
    const float buttonWidth = (ImGui::GetContentRegionAvail().x - spacing * (count - 1.0f)) / count;

    for (size_t i = 0; i < SCALES.size(); ++i) {
        const bool isActive = (i == _selectedScale);

        // Le bouton actif reprend la couleur "appuyé" pour rester repérable
        if (isActive) {
            ImGui::PushStyleColor(ImGuiCol_Button,
                                  ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
        }
        if (ImGui::Button(SCALES[i].label.c_str(), ImVec2(buttonWidth, 0.0f))) {
            _selectedScale = i;
        }
        if (isActive) {
            ImGui::PopStyleColor();
        }

        if (i + 1 < SCALES.size()) {
            ImGui::SameLine();
        }
    }

    ImGui::Spacing();
    ImGui::TextDisabled("Simulation speed");
    ImGui::Text("1 tick = %.0f year(s)", SCALES[_selectedScale].years);
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::templateType::TIME_INTERFACE, [] {
                return std::make_unique<ui::TimeInterfaceContent>();
            });
        }
    } autoRegister;
}