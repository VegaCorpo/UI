#include "Template.hpp"
#include "ITemplateContent.hpp"
#include "lib/TemplateType.hpp"

void ui::Template::createInterface(ui::templateType &type) {
    auto content = ui::makeTemplateContent(type);
    content->render();
}