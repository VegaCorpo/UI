#pragma once

#include <array>
#include "../BaseTemplateContent.hpp"

namespace ui {

class TimeInterfaceContent : public BaseTemplateContent {
private:
    struct ScaleOption {
        const std::string label;
        double years;
    };

    static constexpr std::array<ScaleOption, 4> SCALES = {{
        {"Year",       1.0},
        {"Decade",    10.0},
        {"Century",  100.0},
        {"Millennium", 1000.0}
    }};

    void _renderContent(worldData &data) override;

    size_t _selectedScale = 0;
};

} // namespace ui