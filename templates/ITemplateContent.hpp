#pragma once

#include <iostream>
#include <memory>

#include "lib/TemplateType.hpp"

namespace ui {

    class ITemplateContent {
        public:
            virtual ~ITemplateContent() = default;
            virtual void render() = 0;
    };

    std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type);
} // namespace ui