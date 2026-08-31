#pragma once

#include "../ATemplateContent.hpp"

namespace ui {
    class InfoInterfaceContent : public ATemplateContent {
        public:
            using ATemplateContent::ATemplateContent;
            void render(GLFWwindow *window) override { /* Info interface */ };
    };
}