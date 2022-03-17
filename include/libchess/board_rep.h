#pragma once

#include "libchess/board_state.h"
#include "libchess/square.h"

#include <array>
#include <string>

namespace libchess {

class board_rep {
  public:
    board_rep(const board_state& state);

    [[nodiscard]] const square& get_square(std::size_t x, std::size_t y) const;

    void update(const board_state& state);

    [[nodiscard]] std::string to_string() const;

  private:
    using rep = std::array<std::array<square, 8>, 8>;

    static const rep k_empty_rep;

    rep m_rep;
};

}
