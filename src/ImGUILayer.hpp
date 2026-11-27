#pragma once

#include <array>
#include <imgui.h>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "EntityPreset.hpp"
#include "FrameContent.hpp"
#include "ILayer.hpp"
#include "ITemplateContent.hpp"
#include "types/World.hpp"
#include "WorldData.hpp"

namespace ui {

    struct WindowLayout {
        std::string title;
        ImVec2 position;
        ImVec2 size;
    };

    namespace interfaceConstant {
        inline constexpr float outerMargin = 10.0f;
        inline constexpr float columnGap   = 10.0f;

        // Main Interface
        inline constexpr ImVec2 mainPos  = {outerMargin, outerMargin};
        inline constexpr ImVec2 mainSize = {200.0f, 1000.0f};

        // Time Interface
        inline constexpr ImVec2 timePos  = {mainPos.x + mainSize.x + columnGap, outerMargin};
        inline constexpr ImVec2 timeSize = {410.0f, 120.0f};

        // Edition Menu
        inline constexpr ImVec2 editionPos  = {213.0f, 528.0f};
        inline constexpr ImVec2 editionSize = {1057.0f, 266.0f};

        // Info Window
        inline constexpr ImVec2 infoPos  = {1010.0f, 15.0f};
        inline constexpr ImVec2 infoSize = {250.0f, 200.0f};
    }

    namespace layoutInterface {
        inline constexpr WindowLayout editionWindow {
            .title    = "Edition Menu",
            .position = interfaceConstant::editionPos,
            .size     = interfaceConstant::editionSize,
        };

        inline constexpr WindowLayout infoWindow {
            .title    = "Scene Info",
            .position = interfaceConstant::infoPos,
            .size     = interfaceConstant::infoSize,
        };

        inline constexpr WindowLayout mainWindow {
            .title    = "Main Interface",
            .position = interfaceConstant::mainPos,
            .size     = interfaceConstant::mainSize,
        };

        inline constexpr WindowLayout timeWindow {
            .title    = "Time Interface",
            .position = interfaceConstant::timePos,
            .size     = interfaceConstant::timeSize,
        };
    }

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
            void init(GLFWwindow* window, const common::SpecificDataUI& specificDataUI) override;

            void updateWorldState(const common::WorldState& worldState) override
            {
                this->_data.worldState = worldState;
            }

            bool filterRender(const std::string_view &title);

            void renderFrames();

            void render() override;


            void shutdown() override;

            const common::SpecificDataUI& publish() override { return _data.specificDataUI; }

            std::queue<common::BodyPatch> pollEdits() override { return std::exchange(this->_data.edits, {}); }

            void updateBodies(const common::SpecificDataUI &bodies) override;

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

            // World Data
            worldData _data;

            std::vector<EntityPreset> _presets;
            inline static const std::string PRESETS_PATH = "presets/entity_preset.json";
    };
} // namespace ui
