#pragma once

#include <string>

namespace libchess {

class piece {
  public:
    enum class type : std::uint8_t
    {
        none = 0,
        pawn,
        knight,
        bishop,
        rook,
        queen,
        king
    };

    enum class color : std::uint8_t
    {
        white = 0,
        black
    };

    piece(type piece_type, color piece_color);

    [[nodiscard]] type get_type() const;
    [[nodiscard]] color get_color() const;

    [[nodiscard]] std::string to_string() const;

  private:
    type m_type;
    color m_color;
};

}
