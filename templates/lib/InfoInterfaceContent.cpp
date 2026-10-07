#include "InfoInterfaceContent.hpp"
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "imgui.h"
#include "FrameContent.hpp"

void ui::InfoInterfaceContent::renderWidgets(const std::string &windowTitle,
                                              const frameContent &content,
                                              worldData &data) {
    ImGui::SetNextWindowPos(content.position, content.condition);
    ImGui::SetNextWindowSize(content.size, content.condition);
    ImGui::Begin(windowTitle.c_str());

    const auto &ids = data.specificDataUI.entitiesId;

    if (ids.empty()) {
        ImGui::TextWrapped("No entity available.");
        ImGui::End();
        return;
    }

    if (!_selectedEntityId.has_value() ||
        std::find(ids.begin(), ids.end(), *_selectedEntityId) == ids.end()) {
        _selectedEntityId = ids.front();
    }

    const std::string previewLabel = "Entity " + std::to_string(*_selectedEntityId);
    if (ImGui::BeginCombo("Entity", previewLabel.c_str())) {
        for (size_t id : ids) {
            bool isSelected = (id == *_selectedEntityId);
            std::string label = "Entity " + std::to_string(id);

            if (ImGui::Selectable(label.c_str(), isSelected)) {
                _selectedEntityId = id;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::Separator();

    const size_t entityId = *_selectedEntityId;

    if (auto idx = findEntityIndex(data.specificDataUI.entitiesId, entityId); idx.has_value()) {
        ImGui::TextWrapped("Name: %s", data.specificDataUI.names[*idx].value);
        ImGui::TextWrapped("Mass: %.3f x 10^%d kg",
                    data.specificDataUI.masses[*idx].mantissa,
                    data.specificDataUI.masses[*idx].exponent);
    }

    if (auto idx = findEntityIndex(data.worldState.entitiesId, entityId); idx.has_value()) {
        const auto &pos = data.worldState.positions[*idx];
        const auto &vel = data.worldState.velocities[*idx];
        const auto &acc = data.worldState.accelerations[*idx];

        ImGui::TextWrapped("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
        ImGui::TextWrapped("Velocity: (%.2f, %.2f, %.2f)", vel.x, vel.y, vel.z);
        ImGui::TextWrapped("Acceleration: (%.2f, %.2f, %.2f)", acc.x, acc.y, acc.z);

        if (*idx < data.worldState.collided.size()) {
            ImGui::TextWrapped("Collided: %s", data.worldState.collided[*idx] ? "yes" : "no");
        }
    } else {
        ImGui::TextWrapped("No physics data for this entity.");
    }

    ImGui::End();
}

namespace {
    struct AutoRegister {
        AutoRegister() {
            ui::registerTemplateContent(ui::templateType::INFO_INTERFACE, [] {
                return std::make_unique<ui::InfoInterfaceContent>();
            });
        }
    } autoRegister;
}