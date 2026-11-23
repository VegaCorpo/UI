#include "VisibilitySettings.hpp"

#include <cstdlib>
#include <cstring>
#include <imgui.h>
#include <imgui_internal.h>

namespace {

void *visibilityReadOpen(ImGuiContext *, ImGuiSettingsHandler *handler, const char *name)
{
    return std::strcmp(name, "Visibility") == 0 ? handler->UserData : nullptr;
}

void visibilityReadLine(ImGuiContext *, ImGuiSettingsHandler *, void *entry, const char *line)
{
    auto *map = static_cast<ui::VisibilityMap *>(entry);
    const char *eq = std::strrchr(line, '=');
    if (eq == nullptr) {
        return;
    }
    if (auto it = map->find(std::string(line, eq)); it != map->end()) {
        it->second = (std::atoi(eq + 1) != 0);
    }
}

void visibilityWriteAll(ImGuiContext *, ImGuiSettingsHandler *handler, ImGuiTextBuffer *out)
{
    const auto *map = static_cast<const ui::VisibilityMap *>(handler->UserData);
    out->appendf("[%s][Visibility]\n", handler->TypeName);
    for (const auto &[title, visible] : *map) {
        out->appendf("%s=%d\n", title.c_str(), visible ? 1 : 0);
    }
    out->append("\n");
}

} // namespace

void ui::registerVisibilitySettings(VisibilityMap &map)
{
    ImGuiSettingsHandler handler;
    handler.TypeName   = "OrbitalUI";
    handler.TypeHash   = ImHashStr("OrbitalUI");
    handler.ReadOpenFn = visibilityReadOpen;
    handler.ReadLineFn = visibilityReadLine;
    handler.WriteAllFn = visibilityWriteAll;
    handler.UserData   = &map;
    ImGui::AddSettingsHandler(&handler);
}