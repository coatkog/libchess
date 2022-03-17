#include "sprites.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

sprites::sprites(float piece_width)
    : m_piece_width(piece_width) {
}

void sprites::create() {
    if (!m_texture.loadFromFile("../demo-gui/assets/pieces.png")) {
        // TODO:
    }

    m_texture.setSmooth(true);

    create_from_texture(m_white_king_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::king);
    create_from_texture(m_white_queen_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::queen);
    create_from_texture(m_white_rook_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::rook);
    create_from_texture(m_white_bishop_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::bishop);
    create_from_texture(m_white_knight_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::knight);
    create_from_texture(m_white_pawn_sprite,
                        libchess::piece::color::white,
                        libchess::piece::type::pawn);

    create_from_texture(m_black_king_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::king);
    create_from_texture(m_black_queen_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::queen);
    create_from_texture(m_black_rook_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::rook);
    create_from_texture(m_black_bishop_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::bishop);
    create_from_texture(m_black_knight_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::knight);
    create_from_texture(m_black_pawn_sprite,
                        libchess::piece::color::black,
                        libchess::piece::type::pawn);
}

void sprites::create_from_texture(sf::Sprite& sprite,
                                  libchess::piece::color piece_color,
                                  libchess::piece::type piece_type) {
    sf::IntRect intRect;

    switch (piece_color) {
        case libchess::piece::color::black: {
            switch (piece_type) {
                case libchess::piece::type::none:
                    break;
                case libchess::piece::type::pawn:
                    intRect = sf::IntRect(5 * k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::knight:
                    intRect = sf::IntRect(3 * k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::bishop:
                    intRect = sf::IntRect(2 * k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::rook:
                    intRect = sf::IntRect(4 * k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::queen:
                    intRect = sf::IntRect(k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::king:
                    intRect = sf::IntRect(0 * k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
            }
            break;
        }
        case libchess::piece::color::white: {
            switch (piece_type) {
                case libchess::piece::type::none:
                    break;
                case libchess::piece::type::pawn:
                    intRect = sf::IntRect(5 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::knight:
                    intRect = sf::IntRect(3 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::bishop:
                    intRect = sf::IntRect(2 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::rook:
                    intRect = sf::IntRect(4 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::queen:
                    intRect = sf::IntRect(1 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
                case libchess::piece::type::king:
                    intRect = sf::IntRect(0 * k_texture_piece_width,
                                          0,
                                          k_texture_piece_width,
                                          k_texture_piece_width);
                    break;
            }
            break;
        }
    };

    sprite.setTexture(m_texture);
    sprite.setTextureRect(intRect);
    sprite.setScale(m_piece_width / k_texture_piece_width, m_piece_width / k_texture_piece_width);
}

sf::Sprite& sprites::get_white_king_sprite() {
    return m_white_king_sprite;
}

sf::Sprite& sprites::get_white_queen_sprite() {
    return m_white_queen_sprite;
}

sf::Sprite& sprites::get_white_rook_sprite() {
    return m_white_rook_sprite;
}

sf::Sprite& sprites::get_white_bishop_sprite() {
    return m_white_bishop_sprite;
}

sf::Sprite& sprites::get_white_knight_sprite() {
    return m_white_knight_sprite;
}

sf::Sprite& sprites::get_white_pawn_sprite() {
    return m_white_pawn_sprite;
}

sf::Sprite& sprites::get_black_king_sprite() {
    return m_black_king_sprite;
}

sf::Sprite& sprites::get_black_queen_sprite() {
    return m_black_queen_sprite;
}

sf::Sprite& sprites::get_black_rook_sprite() {
    return m_black_rook_sprite;
}

sf::Sprite& sprites::get_black_bishop_sprite() {
    return m_black_bishop_sprite;
}

sf::Sprite& sprites::get_black_knight_sprite() {
    return m_black_knight_sprite;
}

sf::Sprite& sprites::get_black_pawn_sprite() {
    return m_black_pawn_sprite;
}
