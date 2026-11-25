#pragma once

#include <GLFW/glfw3.h>
#include <queue>
#include "types/BodyPatch.hpp"
#include "types/World.hpp"
#include "types/RenderDataBuffer.hpp"

namespace ui {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Init Methods
            virtual void init(GLFWwindow* window, const common::SpecificDataUI &dataUI) = 0;

            // Recover Worldstate Data
            virtual void updateWorldState(const common::WorldState &worldState) = 0;

            // Render ImGUI Interface
            virtual void render() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;

            // Get all the specificDataUI
            virtual const common::SpecificDataUI &publish() = 0;

            // Body edits made since the last call
            virtual std::queue<common::BodyPatch> pollEdits() = 0;

    };
} // namespace ui
