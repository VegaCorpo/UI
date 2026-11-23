#pragma once

#include "ITemplateContent.hpp"
#include "WorldData.hpp"

namespace ui {
    class BaseTemplateContent : public ITemplateContent {
        public:
            BaseTemplateContent() = default;
            ~BaseTemplateContent() override = default;
            void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) final;
            ImGuiWindowFlags lockBtn() {
                const ImGuiWindowFlags flags = this->_locked
                ? (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
                : ImGuiWindowFlags_None;
                return flags;
            }

        private:
            virtual void _renderContent(worldData &data);
            bool _locked = false;
    };
}