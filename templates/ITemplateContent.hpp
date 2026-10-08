#pragma once

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "WorldData.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(_WIN32)
    #include <windows.h>
    #include <GL/gl.h>
#elif defined(__APPLE__)
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "lib/TemplateType.hpp"

namespace ui {

    struct frameContent;

    class ITemplateContent {
        public:
            virtual ~ITemplateContent() = default;

            // Methods containing all informations in the interface
            virtual void renderWidgets(const std::string &windowTitle,
                                const frameContent &content,
                                worldData &data) = 0;
    };
} // namespace ui