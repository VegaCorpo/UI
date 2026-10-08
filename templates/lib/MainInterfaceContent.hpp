#pragma once

#include "BaseTemplateContent.hpp"
#include "TemplateContentFactory.hpp"
#include "WorldData.hpp"

namespace ui {
    class MainInterfaceContent : public BaseTemplateContent {
        private:
            void renderContent(worldData &data) override;
    };
}