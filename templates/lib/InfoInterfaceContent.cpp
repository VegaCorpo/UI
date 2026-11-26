#include "InfoInterfaceContent.hpp"
#include <cstddef>
#include <cstdint>
#include "TemplateContentFactory.hpp"
#include "TemplateType.hpp"
#include "imgui.h"
#include "FrameContent.hpp"

namespace {
        std::optional<size_t> findEntityIndex(const std::vector<size_t> &ids, size_t entityId) {
        auto it = std::find(ids.begin(), ids.end(), entityId);
        if (it == ids.end()) {
            return std::nullopt;
        }
        return static_cast<size_t>(std::distance(ids.begin(), it));
    }

}

bool ui::InfoInterfaceContent::cameraButton(const char* id, bool& enabled, ui::worldData &data)
{
    constexpr float hoverRounding = 4.0f;
    constexpr float strokeThickness = 2.0f;

    const float buttonSize = ImGui::GetFrameHeight();
    const ImVec2 topLeft = ImGui::GetCursorScreenPos();
    const ImVec2 bottomRight = ImVec2(
        topLeft.x + buttonSize,
        topLeft.y + buttonSize
    );

    const bool clicked = ImGui::InvisibleButton(
        id, ImVec2(buttonSize, buttonSize)
    );

    if (clicked)
        enabled = !enabled;

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    if (ImGui::IsItemHovered())
    {
        drawList->AddRectFilled(
            topLeft,
            bottomRight,
            ImGui::GetColorU32(ImGuiCol_ButtonHovered),
            hoverRounding
        );
    }

    const ImU32 iconColor = ImGui::GetColorU32(ImGuiCol_Text);

    const float cx = topLeft.x + buttonSize * 0.46f;
    const float cy = topLeft.y + buttonSize * 0.50f;

    const float bodyLeft = topLeft.x + buttonSize * 0.18f;
    const float bodyRight = topLeft.x + buttonSize * 0.65f;
    const float bodyTop = topLeft.y + buttonSize * 0.30f;
    const float bodyBottom = topLeft.y + buttonSize * 0.70f;

    drawList->AddRect(
        ImVec2(bodyLeft, bodyTop),
        ImVec2(bodyRight, bodyBottom),
        iconColor,
        2.0f,
        0,
        strokeThickness
    );

    drawList->AddTriangle(
        ImVec2(bodyRight, topLeft.y + buttonSize * 0.38f),
        ImVec2(topLeft.x + buttonSize * 0.88f, topLeft.y + buttonSize * 0.24f),
        ImVec2(topLeft.x + buttonSize * 0.88f, topLeft.y + buttonSize * 0.76f),
        iconColor,
        strokeThickness
    );

    if (!enabled)
    {
        drawList->AddLine(
            ImVec2(topLeft.x + buttonSize * 0.15f,
                   topLeft.y + buttonSize * 0.85f),
            ImVec2(topLeft.x + buttonSize * 0.85f,
                   topLeft.y + buttonSize * 0.15f),
            iconColor,
            strokeThickness
        );
        this->_selectedEntityId = SIZE_MAX;
        data.specificDataUI.camFocusEnt = SIZE_MAX;
    }

    return clicked;
}

void ui::InfoInterfaceContent::selectMenu(const std::vector<size_t> &ids, ui::worldData &data) {
    const std::string previewLabel = "Entity " + std::to_string(*this->_selectedEntityId);
    
    static bool cameraEnabled = false;

    cameraButton("##Camera", cameraEnabled, data);

    ImGui::SameLine();

    if (ImGui::BeginCombo("", previewLabel.c_str())) {
        for (size_t id : ids) {
            bool isSelected = (id == *this->_selectedEntityId);
            std::string label = "Entity " + std::to_string(id);
            if (ImGui::Selectable(label.c_str(), isSelected)) {
                this->_selectedEntityId = id;
                data.specificDataUI.camFocusEnt = id;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

void drawEntityInfo(ui::worldData &data, const size_t entityId) {
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
}

void ui::InfoInterfaceContent::_renderContent(worldData &data) {
    const auto &ids = data.specificDataUI.entitiesId;

    if (ids.empty()) {
        ImGui::TextWrapped("No entity available.");
        ImGui::End();
        return;
    }

    if (!this->_selectedEntityId.has_value() ||
        std::find(ids.begin(), ids.end(), *this->_selectedEntityId) == ids.end()) {
        this->_selectedEntityId = ids.front();
    }

    this->selectMenu(ids, data);

    ImGui::Separator();

    const size_t entityId = *this->_selectedEntityId;

    drawEntityInfo(data, entityId);

    if (ImGui::Button("Delete"))
    {
        // TO DO
        data.specificDataUI.entityToDelete = entityId;
    }
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