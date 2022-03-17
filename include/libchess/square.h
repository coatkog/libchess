#pragma once

#include "libchess/piece.h"

#include <cstdint>
#include <memory>

namespace libchess {

class square {
  public:
    enum class color : std::uint8_t
    {
        white = 0,
        black
    };

    square(color color);

    void set_piece(piece piece);

    [[nodiscard]] color get_color() const;

    [[nodiscard]] piece get_piece() const;
    [[nodiscard]] bool empty() const;

    [[nodiscard]] std::string to_string() const;

  private:
    color m_color;
    piece m_piece;
};

}
