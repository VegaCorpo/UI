#pragma once
#include "BaseTemplateContent.hpp"

namespace ui {
    class InfoInterfaceContent : public BaseTemplateContent {
    public:
        void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) override;
    private:
        std::optional<size_t> _selectedEntityId;
    };
}