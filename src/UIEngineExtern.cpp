#include <memory>
#include "types/ModuleInfo.hpp"
#include "types/types.hpp"
#include "UIEngine.hpp"

extern "C" {

    std::unique_ptr<common::IUIEngine> get_engine()
    {
        // ImGui::DebugLog("Debug from ImGui");
        return std::make_unique<ui::UIEngine>();
    }

    common::ModuleType get_module_type()
    {
        return common::ModuleType::UI;
    }

    common::ModuleInfo get_module_info()
    {
        return {
            .name = ORBITAL_MODULE_NAME,
            .version = ORBITAL_MODULE_VERSION,
            .type = common::ModuleType::UI,
        };
    }
}
