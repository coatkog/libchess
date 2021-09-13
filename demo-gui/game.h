#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <libchess/board.h>

#include "sprites.h"

class Game {
  public:
    Game(float width);

    void Draw(sf::RenderWindow& window);

    void OnClick(int x, int y);

  private:
    static constexpr float kTopLeftPadding = 16.0;
    static constexpr float kBottomRightPadding = 32.0;
    static constexpr float kAvailableMoveCircleRadius = 12.0;
    static constexpr float kLogsSpacing = 20.0;

    static const sf::Color kWhiteSquareColor;
    static const sf::Color kBlackSquareColor;
    static const sf::Color kSelectedSquareColor;
    static const sf::Color kAvailableSquareColor;

    float m_width;
    float m_board_width;
    float m_square_width;

    libchess::Board m_board;
    std::vector<libchess::Move> m_available_moves;

    sf::Font m_font;
    Sprites m_sprites;

    sf::Vector2i m_clicked_square;

    void DoMove(int starting_x, int starting_y, int ending_x, int ending_y);

    void DrawAvailableMoves(sf::RenderWindow& window);

    void DrawBoard(sf::RenderWindow& window);
    void DrawBoardInfo(sf::RenderWindow& window);
    void DrawLogs(sf::RenderWindow& window);
    void DrawPieces(sf::RenderWindow& window);

    sf::Vector2i WindowClickPositionToSquare(int x, int y);

    std::vector<std::string> m_logs;
};
