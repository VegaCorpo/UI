#include "TemplateContentFactory.hpp"
#include "ATemplateContent.hpp"
#include "./lib/InfoInterfaceContent.hpp"
#include "./lib/MainInterfaceContent.hpp"

std::unique_ptr<ui::ITemplateContent> ui::makeTemplateContent(templateType type) {
    switch (type) {
        case MAIN_INTERFACE: return std::make_unique<MainInterfaceContent>();
        case INFO_INTERFACE: return std::make_unique<InfoInterfaceContent>();
        default:             return std::make_unique<ATemplateContent>();
    }
}