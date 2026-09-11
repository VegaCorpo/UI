#include "TemplateContentFactory.hpp"
#include "ATemplateContent.hpp"

static std::unordered_map<ui::templateType, ui::ContentCreator> &registry() {
    static std::unordered_map<ui::templateType, ui::ContentCreator> instance;
    return instance;
}

void ui::registerTemplateContent(templateType type, ContentCreator creator) {
    registry()[type] = std::move(creator);
}

std::unique_ptr<ui::ITemplateContent> ui::makeTemplateContent(templateType type) {
    auto it = registry().find(type);
    if (it != registry().end()) {
        return it->second();
    }
    return std::make_unique<ATemplateContent>();
}