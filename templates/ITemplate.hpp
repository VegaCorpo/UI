#pragma once

#include "lib/TemplateType.hpp"


namespace ui {
    class ITemplate {
        public:
            virtual ~ITemplate() = default;

            virtual void createInterface(templateType &type) = 0;
    };
} // namespace ui
