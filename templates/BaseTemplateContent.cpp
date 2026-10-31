#include "BaseTemplateContent.hpp"
#include <components/mass.hpp>
#include "FrameContent.hpp"
#include "WorldData.hpp"
#include "preset/Preset.hpp"

#include <cfloat>
#include <type_traits>

void ui::BaseTemplateContent::renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                [[maybe_unused]] worldData &data) {
    ImGui::SetNextWindowPos(content.position, content.condition);
    ImGui::SetNextWindowSize(content.size, content.condition);
    ImGui::Begin(windowTitle.c_str());

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
    for (const auto &preset : common::presets::PRESET) {
        if (ImGui::Selectable(preset.label)) {
            data.specificDataUI.entityAsked = common::EntitySpawnRequest::fromPreset(preset);
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