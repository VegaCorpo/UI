#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
// Sur Linux : imgui_impl_x11 ou imgui_impl_sdl2 selon ce que Godot utilise
// Sur Windows : imgui_impl_win32
#include "imgui_impl_sdl2.h"
#include <SDL2/SDL.h>

// #include "UIRenderData.hpp" le fichier core contenant le type de buffer

namespace ui {

    class ImGUILayer {
        public:
            ~ImGUILayer() = default;

            bool initWithRenderer(void *native_window, void *gl_context);

            void beginFrame();
            // UIRenderData  endFrame(); envoie le buffer ajouter les types de buffer dans le core
            void shutdown();

    };
} // namespace ui