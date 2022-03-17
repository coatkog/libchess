#include "game.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <chrono>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory>

const sf::Color game::k_white_square_color = sf::Color::White;
const sf::Color game::k_black_square_color = sf::Color(128, 128, 128);
const sf::Color game::k_selected_square_color = sf::Color::Red;
const sf::Color game::k_available_square_color = sf::Color(192, 192, 192);

game::game(float width)
    : m_width(width)
    , m_board_width(width - k_top_left_padding - k_bottom_right_padding)
    , m_square_width((width - k_top_left_padding - k_bottom_right_padding) / 8)
    , m_sprites(m_square_width)
    , m_clicked_square(-1, -1) {
    m_sprites.create();

    if (!m_font.loadFromFile("../demo-gui/assets/ClearSans-Regular.ttf")) {
        // TODO:
    }
}

void game::draw(sf::RenderWindow& window) {
    draw_board(window);
    draw_board_info(window);
    draw_pieces(window);

    draw_available_moves(window);
}

void game::on_click(int x, int y) {
    if (x < k_top_left_padding || x > k_top_left_padding + m_board_width) {
        return;
    }
    if (y < k_top_left_padding || y > k_top_left_padding + m_board_width) {
        return;
    }

    if (m_clicked_square.x != -1) {
        sf::Vector2i new_clicked_square = window_click_position_to_square(x, y);

        do_move(m_clicked_square.x, m_clicked_square.y, new_clicked_square.x, new_clicked_square.y);

        m_clicked_square.x = -1;
        m_clicked_square.y = -1;
    } else {
        m_clicked_square = window_click_position_to_square(x, y);

        m_available_moves = m_board.get_available_moves(m_clicked_square.x, m_clicked_square.y);
    }
}

void game::do_move(int starting_x, int starting_y, int ending_x, int ending_y) {
    try {
        m_board.do_move(starting_x, starting_y, ending_x, ending_y);
    } catch (const std::exception&) {
    }
}

void game::draw_board(sf::RenderWindow& window) {
    sf::RectangleShape board(sf::Vector2f(m_board_width, m_board_width));
    board.setOutlineThickness(2);
    board.setOutlineColor(sf::Color::Black);
    board.setPosition(sf::Vector2f(k_top_left_padding, k_top_left_padding));

    window.draw(board);

    for (std::size_t x = 0; x < 8; x++) {
        for (std::size_t y = 0; y < 8; y++) {
            const libchess::square& square = m_board.get_square(x, y);

            sf::RectangleShape square_shape(sf::Vector2f(m_square_width, m_square_width));

            if (m_clicked_square.x == static_cast<int>(x) &&
                m_clicked_square.y == static_cast<int>(y)) {
                square_shape.setFillColor(k_selected_square_color);
            } else {
                if (square.get_color() == libchess::square::color::white) {
                    square_shape.setFillColor(k_white_square_color);
                } else {
                    square_shape.setFillColor(k_black_square_color);
                }
            }

            square_shape.setPosition(sf::Vector2f(k_top_left_padding + x * m_square_width,
                                                  k_top_left_padding + y * m_square_width));

            window.draw(square_shape);
        }
    }
}

void game::draw_board_info(sf::RenderWindow& window) {
    for (std::size_t i = 0; i < 8; i++) {
        sf::Text text;
        text.setFont(m_font);
        text.setFillColor(sf::Color::Black);

        float char_size = m_width / 50;
        text.setCharacterSize(char_size);

        text.setString(static_cast<char>('A' + i));
        text.setPosition(
            sf::Vector2f(k_top_left_padding + m_square_width / 2 + i * m_square_width - char_size / 2,
                         m_width - k_bottom_right_padding / 2 - char_size / 2));
        window.draw(text);

        text.setString(static_cast<char>('8' - i));
        text.setPosition(sf::Vector2f(
            m_width - k_bottom_right_padding / 2 - char_size / 2,
            k_top_left_padding + m_square_width / 2 + i * m_square_width - char_size / 2));
        window.draw(text);
    }
}

void game::draw_pieces(sf::RenderWindow& window) {
    for (std::size_t x = 0; x < 8; x++) {
        for (std::size_t y = 0; y < 8; y++) {
            const libchess::square& square = m_board.get_square(x, y);

            if (square.empty()) {
                continue;
            }

            sf::Sprite* sprite = nullptr;

            libchess::piece::color piece_color = square.get_piece().get_color();
            libchess::piece::type piece_type = square.get_piece().get_type();

            switch (piece_color) {
                case libchess::piece::color::black: {
                    switch (piece_type) {
                        case libchess::piece::type::none:
                            break;
                        case libchess::piece::type::pawn:
                            sprite = &m_sprites.get_black_pawn_sprite();
                            break;
                        case libchess::piece::type::knight:
                            sprite = &m_sprites.get_black_knight_sprite();
                            break;
                        case libchess::piece::type::bishop:
                            sprite = &m_sprites.get_black_bishop_sprite();
                            break;
                        case libchess::piece::type::rook:
                            sprite = &m_sprites.get_black_rook_sprite();
                            break;
                        case libchess::piece::type::queen:
                            sprite = &m_sprites.get_black_queen_sprite();
                            break;
                        case libchess::piece::type::king:
                            sprite = &m_sprites.get_black_king_sprite();
                            break;
                    }
                    break;
                }
                case libchess::piece::color::white: {
                    switch (piece_type) {
                        case libchess::piece::type::none:
                            break;
                        case libchess::piece::type::pawn:
                            sprite = &m_sprites.get_white_pawn_sprite();
                            break;
                        case libchess::piece::type::knight:
                            sprite = &m_sprites.get_white_knight_sprite();
                            break;
                        case libchess::piece::type::bishop:
                            sprite = &m_sprites.get_white_bishop_sprite();
                            break;
                        case libchess::piece::type::rook:
                            sprite = &m_sprites.get_white_rook_sprite();
                            break;
                        case libchess::piece::type::queen:
                            sprite = &m_sprites.get_white_queen_sprite();
                            break;
                        case libchess::piece::type::king: {
                            sprite = &m_sprites.get_white_king_sprite();
                            break;
                        }
                    }
                    break;
                }
            }

            if (sprite == nullptr) {
                continue;
            }

            sprite->setPosition(sf::Vector2f(k_top_left_padding + x * m_square_width,
                                             k_top_left_padding + y * m_square_width));
            window.draw(*sprite);
        }
    }
}

void game::draw_available_moves(sf::RenderWindow& window) {
    if (m_clicked_square.x == -1) {
        return;
    }

    sf::CircleShape dot(k_available_move_circle_radius);
    dot.setFillColor(k_available_square_color);

    for (const auto& move : m_available_moves) {
        dot.setPosition(sf::Vector2f(k_top_left_padding + move.ending_x * m_square_width +
                                         m_square_width / 2 - k_available_move_circle_radius,
                                     k_top_left_padding + move.ending_y * m_square_width +
                                         m_square_width / 2 - k_available_move_circle_radius));

        window.draw(dot);
    }
}

sf::Vector2i game::window_click_position_to_square(int x, int y) {
    return sf::Vector2i(static_cast<int>((x - k_top_left_padding) / m_square_width),
                        static_cast<int>((y - k_top_left_padding) / m_square_width));
}
