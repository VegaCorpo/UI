#pragma once

#include <array>
#include <imgui.h>
#include <map>
#include <vector>
#include "ILayer.hpp"
#include "ITemplateContent.hpp"
#include "types/World.hpp"
#include "WorldData.hpp"
#include "ITemplateContent.hpp"
#include "FrameContent.hpp"


namespace ui {

    class ImGUILayer : public ui::ILayer {
        public:
            ImGUILayer() : _isShutdown(false) {};
            ~ImGUILayer() override
            {
                if (!this->_isShutdown) {
                    this->shutdown();
                }
            };

            void guiFrameCreation();
            void init(GLFWwindow* window, const common::SpecificDataUI &specificDataUI) override;

            void updateWorldState(const common::WorldState &worldState) override { this->_data.worldState = worldState; }

            void render() override;

            void shutdown() override;

        private:
            // GUI Interface Methods
            void _setupStyle();
            void _mainMenu();

            // Private Attributs
            common::RenderDataBuffer _buffer;
            GLFWwindow* _window = nullptr;
            bool _isShutdown;
            unsigned int _fontTextureId = 0;

            // ImGUI Frame
            std::map<std::string, frameContent> _guiFrames;
            std::vector<std::string> _framesTitle;

            const std::string CONTEXT_TITLE = "Context 1";
            inline static constexpr std::array<ImVec2, 2> CONTEXT_CONTENT = {
                ImVec2(210, 645),
                ImVec2(1055, 150)
            };

            const std::string INFO_TITLE = "Info 1";
            inline static constexpr std::array<ImVec2, 2> INFO_CONTENT = {
                ImVec2(1010,15),
                ImVec2(250, 200)
            };

            const std::string MAIN_TITLE = "Main Interface";
            inline static constexpr std::array<ImVec2, 2> MAIN_CONTENT = {
                ImVec2(10, 10),
                ImVec2(200, 1000)
            };

            // World Data
            worldData _data;

    };
} // namespace ui
