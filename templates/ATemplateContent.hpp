#pragma once

#include "ITemplateContent.hpp"

namespace ui {
    class ATemplateContent : public ITemplateContent {
        public:
            ~ATemplateContent() override = default;
            void render() override;
    };
}