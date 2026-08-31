#pragma once

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <imgui.h>
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

    class ITemplateContent {
        public:
            virtual ~ITemplateContent() = default;
            virtual void render(GLFWwindow *window) = 0;
    };
} // namespace ui