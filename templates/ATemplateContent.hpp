#pragma once

#include "ITemplateContent.hpp"

namespace ui {
    class ATemplateContent : public ITemplateContent {
        public:
            ATemplateContent() = default;
            ~ATemplateContent() override = default;
            void render(GLFWwindow *window) override;
    };
}