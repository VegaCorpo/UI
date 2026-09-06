#pragma once
#include <memory>
#include "ITemplateContent.hpp"
#include <functional>


namespace ui {
    using ContentCreator = std::function<std::unique_ptr<ITemplateContent>()>;

    void registerTemplateContent(templateType type, ContentCreator creator);
    std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type);
}