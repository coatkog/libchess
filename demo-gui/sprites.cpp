#include "sprites.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

Sprites::Sprites(float piece_width)
    : m_piece_width(piece_width) {
}

void Sprites::Create() {
    if (!m_texture.loadFromFile("../demo-gui/assets/pieces.png")) {
        // TODO:
    }

    m_texture.setSmooth(true);

    CreateFromTexture(m_white_king_sprite, libchess::PieceColor::WHITE, libchess::PieceType::KING);
    CreateFromTexture(m_white_queen_sprite, libchess::PieceColor::WHITE, libchess::PieceType::QUEEN);
    CreateFromTexture(m_white_rook_sprite, libchess::PieceColor::WHITE, libchess::PieceType::ROOK);
    CreateFromTexture(m_white_bishop_sprite,
                      libchess::PieceColor::WHITE,
                      libchess::PieceType::BISHOP);
    CreateFromTexture(m_white_knight_sprite,
                      libchess::PieceColor::WHITE,
                      libchess::PieceType::KNIGHT);
    CreateFromTexture(m_white_pawn_sprite, libchess::PieceColor::WHITE, libchess::PieceType::PAWN);

    CreateFromTexture(m_black_king_sprite, libchess::PieceColor::BLACK, libchess::PieceType::KING);
    CreateFromTexture(m_black_queen_sprite, libchess::PieceColor::BLACK, libchess::PieceType::QUEEN);
    CreateFromTexture(m_black_rook_sprite, libchess::PieceColor::BLACK, libchess::PieceType::ROOK);
    CreateFromTexture(m_black_bishop_sprite,
                      libchess::PieceColor::BLACK,
                      libchess::PieceType::BISHOP);
    CreateFromTexture(m_black_knight_sprite,
                      libchess::PieceColor::BLACK,
                      libchess::PieceType::KNIGHT);
    CreateFromTexture(m_black_pawn_sprite, libchess::PieceColor::BLACK, libchess::PieceType::PAWN);
}

void Sprites::CreateFromTexture(sf::Sprite& sprite,
                                libchess::PieceColor piece_color,
                                libchess::PieceType piece_type) {
    std::unique_ptr<sf::IntRect> intRect;

    switch (piece_color) {
        case libchess::PieceColor::BLACK: {
            switch (piece_type) {
                case libchess::PieceType::PAWN:
                    intRect = std::make_unique<sf::IntRect>(5 * kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::KNIGHT:
                    intRect = std::make_unique<sf::IntRect>(3 * kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::BISHOP:
                    intRect = std::make_unique<sf::IntRect>(2 * kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::ROOK:
                    intRect = std::make_unique<sf::IntRect>(4 * kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::QUEEN:
                    intRect = std::make_unique<sf::IntRect>(kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::KING:
                    intRect = std::make_unique<sf::IntRect>(0 * kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
            }
            break;
        }
        case libchess::PieceColor::WHITE: {
            switch (piece_type) {
                case libchess::PieceType::PAWN:
                    intRect = std::make_unique<sf::IntRect>(5 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::KNIGHT:
                    intRect = std::make_unique<sf::IntRect>(3 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::BISHOP:
                    intRect = std::make_unique<sf::IntRect>(2 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::ROOK:
                    intRect = std::make_unique<sf::IntRect>(4 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::QUEEN:
                    intRect = std::make_unique<sf::IntRect>(1 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
                case libchess::PieceType::KING:
                    intRect = std::make_unique<sf::IntRect>(0 * kTexturePieceWidth,
                                                            0,
                                                            kTexturePieceWidth,
                                                            kTexturePieceWidth);
                    break;
            }
            break;
        }
    };

    sprite.setTexture(m_texture);
    sprite.setTextureRect(*intRect);
    sprite.setScale(m_piece_width / kTexturePieceWidth, m_piece_width / kTexturePieceWidth);
}

sf::Sprite& Sprites::GetWhiteKingSprite() {
    return m_white_king_sprite;
}

sf::Sprite& Sprites::GetWhiteQueenSprite() {
    return m_white_queen_sprite;
}

sf::Sprite& Sprites::GetWhiteRookSprite() {
    return m_white_rook_sprite;
}

sf::Sprite& Sprites::GetWhiteBishopSprite() {
    return m_white_bishop_sprite;
}

sf::Sprite& Sprites::GetWhiteKnightSprite() {
    return m_white_knight_sprite;
}

sf::Sprite& Sprites::GetWhitePawnSprite() {
    return m_white_pawn_sprite;
}

sf::Sprite& Sprites::GetBlackKingSprite() {
    return m_black_king_sprite;
}

sf::Sprite& Sprites::GetBlackQueenSprite() {
    return m_black_queen_sprite;
}

sf::Sprite& Sprites::GetBlackRookSprite() {
    return m_black_rook_sprite;
}

sf::Sprite& Sprites::GetBlackBishopSprite() {
    return m_black_bishop_sprite;
}

sf::Sprite& Sprites::GetBlackKnightSprite() {
    return m_black_knight_sprite;
}

sf::Sprite& Sprites::GetBlackPawnSprite() {
    return m_black_pawn_sprite;
}
