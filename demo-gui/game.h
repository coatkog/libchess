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
    static constexpr float kTopLeftPadding = 16;
    static constexpr float kBottomRightPadding = 32;

    static const sf::Color kWhiteSquareColor;
    static const sf::Color kBlackSquareColor;
    static const sf::Color kSelectedSquareColor;

    float _width;
    float _board_width;
    float _square_width;

    libchess::Board _board;

    sf::Font _font;
    Sprites _sprites;

    sf::Vector2i _clicked_square;

    void DoMove(int starting_x, int starting_y, int ending_x, int ending_y);

    void DrawBoard(sf::RenderWindow& window);
    void DrawPieces(sf::RenderWindow& window);

    sf::Vector2i WindowClickPositionToSquare(int x, int y);
};
