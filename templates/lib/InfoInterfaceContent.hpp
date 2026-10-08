#pragma once
#include "BaseTemplateContent.hpp"

namespace ui {
    class InfoInterfaceContent : public BaseTemplateContent {
        public:
            void selectMenu(const std::vector<size_t> &ids);

        private:
            void _renderContent(worldData &data) override;
            std::optional<size_t> _selectedEntityId;
    };
}