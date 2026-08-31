#pragma once

#include "../ATemplateContent.hpp"

namespace ui {
    class MainInterfaceContent : public ATemplateContent {
        public:
            using ATemplateContent::ATemplateContent;
            void render(GLFWwindow *window) override { /* Default interface */ };
    };
}