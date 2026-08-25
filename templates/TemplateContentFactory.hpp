#pragma once
#include <memory>
#include "ITemplateContent.hpp"

namespace ui {
    std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type);
}