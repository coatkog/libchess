#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <libchess/board.h>

#include "sprites.h"

class game {
  public:
    game(float width);

    void draw(sf::RenderWindow& window);

    void on_click(int x, int y);

  private:
    static constexpr float k_top_left_padding = 16.0;
    static constexpr float k_bottom_right_padding = 32.0;
    static constexpr float k_available_move_circle_radius = 12.0;

    static const sf::Color k_white_square_color;
    static const sf::Color k_black_square_color;
    static const sf::Color k_selected_square_color;
    static const sf::Color k_available_square_color;

    float m_width;
    float m_board_width;
    float m_square_width;

    libchess::board m_board;
    std::vector<libchess::move> m_available_moves;

    sf::Font m_font;
    sprites m_sprites;

    sf::Vector2i m_clicked_square;

    void do_move(int starting_x, int starting_y, int ending_x, int ending_y);

    void draw_board(sf::RenderWindow& window);
    void draw_board_info(sf::RenderWindow& window);
    void draw_pieces(sf::RenderWindow& window);

    void draw_available_moves(sf::RenderWindow& window);

    sf::Vector2i window_click_position_to_square(int x, int y);
};
