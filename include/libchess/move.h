#pragma once

#include <iostream>
#include <string>

namespace libchess {

struct move {
    move(const std::string& move_str);
    move(int starting_x, int starting_y, int ending_x, int ending_y);

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] bool valid() const;

    [[nodiscard]] bool is_short_castle() const;
    [[nodiscard]] bool is_long_castle() const;

    bool operator==(const move& rhs) const;

    int starting_x;
    int starting_y;
    int ending_x;
    int ending_y;
};

}
