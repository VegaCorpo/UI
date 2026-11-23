#include "BaseTemplateContent.hpp"
#include <components/mass.hpp>
#include "FrameContent.hpp"
#include "WorldData.hpp"
#include <cfloat>
#include <type_traits>
#include <imgui_internal.h>

namespace {

bool lockButton(const char *id, bool &locked)
{
    constexpr float hoverRounding = 4.0f;
    constexpr float bodyRounding = 2.0f;
    constexpr float strokeThickness = 1.8f;

    constexpr float bodyTopRatio = 0.48f;
    constexpr float bodyBottomRatio = 0.82f;
    constexpr float bodyLeftRatio = 0.25f;
    constexpr float bodyRightRatio = 0.75f;

    constexpr float shackleRadiusRatio = 0.17f;
    constexpr float shackleCenterXRatio = 0.5f;
    constexpr float shackleLiftRatio = 0.14f;
    constexpr float shackleStartAngle = IM_PI;
    constexpr float shackleEndAngle = 2.0f * IM_PI;
    constexpr int shackleArcSegments = 12;

    const float buttonSize = ImGui::GetFrameHeight();
    const ImVec2 topLeft = ImGui::GetCursorScreenPos();
    const ImVec2 bottomRight = ImVec2(topLeft.x + buttonSize, topLeft.y + buttonSize);

    const bool clicked = ImGui::InvisibleButton(id, ImVec2(buttonSize, buttonSize));
    if (clicked) {
        locked = !locked;
    }

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    if (ImGui::IsItemHovered()) {
        drawList->AddRectFilled(topLeft, bottomRight,
                                ImGui::GetColorU32(ImGuiCol_ButtonHovered), hoverRounding);
    }

    const ImU32 iconColor = ImGui::GetColorU32(ImGuiCol_Text);
    const float bodyTop = topLeft.y + bodyTopRatio * buttonSize;
    const float bodyBottom = topLeft.y + bodyBottomRatio * buttonSize;
    const float bodyLeft = topLeft.x + bodyLeftRatio * buttonSize;
    const float bodyRight = topLeft.x + bodyRightRatio * buttonSize;

    drawList->AddRectFilled(ImVec2(bodyLeft, bodyTop),
                            ImVec2(bodyRight, bodyBottom), iconColor, bodyRounding);

    const float shackleRadius = shackleRadiusRatio * buttonSize;
    const float shackleCenterX = topLeft.x + shackleCenterXRatio * buttonSize;
    const float shackleLift = locked ? 0.0f : shackleLiftRatio * buttonSize;
    const float shackleCenterY = bodyTop - shackleLift;

    drawList->PathArcTo(ImVec2(shackleCenterX, shackleCenterY), shackleRadius,
                        shackleStartAngle, shackleEndAngle, shackleArcSegments);
    drawList->PathStroke(iconColor, 0, strokeThickness);

    const float shackleLeftX = shackleCenterX - shackleRadius;
    const float shackleRightX = shackleCenterX + shackleRadius;
    drawList->AddLine(ImVec2(shackleLeftX, shackleCenterY),
                      ImVec2(shackleLeftX, bodyTop), iconColor, strokeThickness);

    if (locked) {
        drawList->AddLine(ImVec2(shackleRightX, shackleCenterY),
                          ImVec2(shackleRightX, bodyTop), iconColor, strokeThickness);
    }

    return clicked;
}

} // namespace

void ui::BaseTemplateContent::renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                [[maybe_unused]] worldData &data) {
    ImGui::SetNextWindowPos(content.position, content.condition);
    ImGui::SetNextWindowSize(content.size, content.condition);
    ImGui::Begin(windowTitle.c_str(), nullptr, this->lockBtn());

    ImGuiWindow *window = ImGui::GetCurrentWindow();
    if (!window->SkipItems) {
        const ImRect titleBar = window->TitleBarRect();
        const float s = ImGui::GetFrameHeight();
        const ImVec2 savedCursor = ImGui::GetCursorScreenPos();

        ImGui::PushClipRect(titleBar.Min, titleBar.Max, false);
        ImGui::SetCursorScreenPos(ImVec2(titleBar.Max.x - s - ImGui::GetStyle().FramePadding.x,
                                         titleBar.Min.y));
        lockButton("##lock", this->_locked);
        ImGui::PopClipRect();

        ImGui::SetCursorScreenPos(savedCursor);
    }

    this->_renderContent(data);

    ImGui::End();
}

namespace {

template <typename T>
constexpr ImGuiDataType imguiDataType() {
    if constexpr (std::is_same_v<T, double>)
        return ImGuiDataType_Double;
    else if constexpr (std::is_same_v<T, float>)
        return ImGuiDataType_Float;
    else if constexpr (std::is_same_v<T, int>)
        return ImGuiDataType_S32;
    else
        static_assert(sizeof(T) == 0, "type not supported by imguiDataType");
}

void inputMass(common::components::Mass &mass) {
    using M = std::remove_cv_t<decltype(mass.mantissa)>;
    using E = std::remove_cv_t<decltype(mass.exponent)>;

    ImGui::PushID("Mass");
    ImGui::TextUnformatted("Mass");
    const float width = ImGui::GetContentRegionAvail().x;
    ImGui::SetNextItemWidth(width * 0.65f);
    ImGui::InputScalar("##mantissa", imguiDataType<M>(), &mass.mantissa);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputScalar("##exponent", imguiDataType<E>(), &mass.exponent);
    ImGui::PopID();
}

void inputRadius(common::components::Radius &radius) {
    using R = std::remove_cv_t<decltype(radius.value)>;

    ImGui::PushID("Radius");
    ImGui::TextUnformatted("Radius");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputScalar("##radius", imguiDataType<R>(), &radius.value);
    ImGui::PopID();
}

template <typename V>
void inputVec3(const char *label, V &v) {
    using T = std::remove_cv_t<decltype(V::x)>;
    static_assert(sizeof(V) == 3 * sizeof(T), "V must be exactly {x, y, z}");

    ImGui::PushID(label);
    ImGui::TextUnformatted(label);
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputScalarN("##value", imguiDataType<T>(), &v.x, 3);
    ImGui::PopID();
}

template <typename Q>
void inputQuat(const char *label, Q &q) {
    using T = std::remove_cv_t<decltype(Q::x)>;
    static_assert(sizeof(Q) == 4 * sizeof(T), "Q must be exactly 4 components");

    ImGui::PushID(label);
    ImGui::TextUnformatted(label);
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputScalarN("##value", imguiDataType<T>(), &q.x, 4);
    ImGui::PopID();
}

} // namespace

void ui::BaseTemplateContent::_renderContent(worldData &data) {
    ImGui::TextUnformatted("Preset");
    for (const auto &preset : *data.presets) {
        if (ImGui::Selectable(preset.label.c_str())) {
            data.specificDataUI.entityAsked = makeSpawnRequest(preset);
        }
    }

    auto &entityAsked = data.specificDataUI.entityAsked;
    if (!entityAsked.has_value())
        return;
    auto &draft = *entityAsked;

    ImGui::Separator();

    ImGui::TextUnformatted("Name");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##name", draft.name.value, sizeof(draft.name.value));

    inputMass(draft.mass);
    inputRadius(draft.radius);
    inputVec3("Position", draft.position);
    inputVec3("Velocity", draft.velocity);
    inputVec3("Acceleration", draft.acceleration);
    inputQuat("Orientation", draft.orientation);

    ImGui::Spacing();
    const bool valid = draft.name.value[0] != '\0'
                    && draft.mass.mantissa > 0
                    && draft.radius.value > 0;
    ImGui::BeginDisabled(!valid);
    if (ImGui::Button("Add entity", ImVec2(-FLT_MIN, 0.0f))) {
        data.specificDataUI.spawnRequested = true;
    }
    ImGui::EndDisabled();
}