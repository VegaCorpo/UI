#pragma once

#include "ITemplate.hpp"
#include "lib/TemplateType.hpp"

namespace ui {
    class Template : public ITemplate{
        public:
            ~Template() override = default;
            void createInterface(templateType &type) override;
    };
}