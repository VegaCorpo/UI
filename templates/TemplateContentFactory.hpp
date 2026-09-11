#pragma once
#include <memory>
#include "ITemplateContent.hpp"
#include <functional>


namespace ui {
    using ContentCreator = std::function<std::unique_ptr<ITemplateContent>()>;

    // Function to register all GUI Template
    void registerTemplateContent(templateType type, ContentCreator creator);

    // Function that return a template object containing its render method
    std::unique_ptr<ITemplateContent> makeTemplateContent(templateType type);
}