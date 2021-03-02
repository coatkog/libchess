#include <string>

namespace libchess {

class Board {
  public:
    Board();

    const std::string& GetFen();
    std::string GetPrintableString() const;

  private:
    static constexpr const char* kStartingFen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    static constexpr std::size_t kBoardHeight = 8;
    static constexpr std::size_t kBoardWidth = 8;

    std::string _fen;

    static std::string FenToHumanReadableString(const std::string& fen);
};

}
