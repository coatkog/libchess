#include <array>
#include <cstdint>

namespace libchess::constants {

// Move indexes
// *******
// **1*2**
// *0***3*
// ***K***
// *4***7*
// **5*6**
struct knight_moves_t {
    std::uint64_t possible_moves;
    static constexpr std::array<int, 8> xs { -2, -1, 1, 2, -2, -1, 1, 2 };
    static constexpr std::array<int, 8> ys { -1, -2, -2, -1, 1, 2, 2, 1 };
};

static constexpr std::array<knight_moves_t, 64> knight_moves {
    { { 0b00000000'00100000'01000000'00000000'00000000'00000000'00000000'00000000 },
      { 0b00000000'00010000'10100000'00000000'00000000'00000000'00000000'00000000 },
      { 0b00000000'10001000'01010000'00000000'00000000'00000000'00000000'00000000 } }
};

}
