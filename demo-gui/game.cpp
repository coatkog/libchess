#include "game.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <exception>
#include <iterator>
#include <memory>
#include <sstream>

const sf::Color Game::kWhiteSquareColor = sf::Color::White;
const sf::Color Game::kBlackSquareColor = sf::Color(128, 128, 128);
const sf::Color Game::kSelectedSquareColor = sf::Color::Red;

Game::Game(float width)
    : _width(width)
    , _board_width(width - kTopLeftPadding - kBottomRightPadding)
    , _square_width((width - kTopLeftPadding - kBottomRightPadding) / 8)
    , _sprites(_square_width)
    , _clicked_square(-1, -1) {
    _sprites.Create();

    if (!_font.loadFromFile("../demo-gui/assets/Roboto-Regular.ttf")) {
        // TODO:
    }
}

void Game::Draw(sf::RenderWindow& window) {
    DrawBoard(window);
    DrawPieces(window);
}

void Game::OnClick(int x, int y) {
    if (_clicked_square.x != -1) {
        sf::Vector2i new_clicked_square = WindowClickPositionToSquare(x, y);

        DoMove(_clicked_square.x, _clicked_square.y, new_clicked_square.x, new_clicked_square.y);

        _clicked_square.x = -1;
        _clicked_square.y = -1;
    } else {
        _clicked_square = WindowClickPositionToSquare(x, y);
    }
}

void Game::DoMove(int starting_x, int starting_y, int ending_x, int ending_y) {
    std::stringstream ss;

    ss << static_cast<char>('a' + starting_x);
    ss << static_cast<char>('8' - starting_y);
    ss << static_cast<char>('a' + ending_x);
    ss << static_cast<char>('8' - ending_y);

    try {
        _board.DoMove(ss.str());
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Game::DrawBoard(sf::RenderWindow& window) {
    sf::RectangleShape board(sf::Vector2f(_board_width, _board_width));
    board.setOutlineThickness(2);
    board.setOutlineColor(sf::Color::Black);
    board.setPosition(sf::Vector2f(kTopLeftPadding, kTopLeftPadding));

    window.draw(board);

    for (std::size_t i = 0; i < 8; i++) {
        for (std::size_t j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(_square_width, _square_width));

            if (_clicked_square.x == static_cast<int>(j) &&
                _clicked_square.y == static_cast<int>(i)) {
                square.setFillColor(kSelectedSquareColor);
            } else {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                    square.setFillColor(kWhiteSquareColor);
                } else {
                    square.setFillColor(kBlackSquareColor);
                }
            }

            square.setPosition(sf::Vector2f(kTopLeftPadding + j * _square_width,
                                            kTopLeftPadding + i * _square_width));

            window.draw(square);
        }
    }

    for (std::size_t i = 0; i < 8; i++) {
        sf::Text text;
        text.setFont(_font);
        text.setFillColor(sf::Color::Black);

        float char_size = _width / 50;
        text.setCharacterSize(char_size);

        text.setString(static_cast<char>('A' + i));
        text.setPosition(
            sf::Vector2f(kTopLeftPadding + _square_width / 2 + i * _square_width - char_size / 2,
                         _width - kBottomRightPadding / 2 - char_size / 2));
        window.draw(text);

        text.setString(static_cast<char>('8' - i));
        text.setPosition(
            sf::Vector2f(_width - kBottomRightPadding / 2 - char_size / 2,
                         kTopLeftPadding + _square_width / 2 + i * _square_width - char_size / 2));
        window.draw(text);
    }
}

void Game::DrawPieces(sf::RenderWindow& window) {
    for (std::size_t i = 0; i < 8; i++) {
        for (std::size_t j = 0; j < 8; j++) {
            libchess::Square square = _board.GetBoard()[i][j];

            if (!square.ContainsPiece()) {
                continue;
            }

            sf::Sprite* sprite = nullptr;
            sf::Vector2f position(kTopLeftPadding + j * _square_width,
                                  kTopLeftPadding + i * _square_width);

            libchess::PieceColor piece_color = square.GetPieceColor();
            libchess::PieceType piece_type = square.GetPieceType();

            switch (piece_color) {
                case libchess::PieceColor::BLACK: {
                    switch (piece_type) {
                        case libchess::PieceType::PAWN:
                            sprite = &_sprites.GetBlackPawnSprite();
                            break;
                        case libchess::PieceType::KNIGHT:
                            sprite = &_sprites.GetBlackKnightSprite();
                            break;
                        case libchess::PieceType::BISHOP:
                            sprite = &_sprites.GetBlackBishopSprite();
                            break;
                        case libchess::PieceType::ROOK:
                            sprite = &_sprites.GetBlackRookSprite();
                            break;
                        case libchess::PieceType::QUEEN:
                            sprite = &_sprites.GetBlackQueenSprite();
                            break;
                        case libchess::PieceType::KING:
                            sprite = &_sprites.GetBlackKingSprite();
                            break;
                    }
                    break;
                }
                case libchess::PieceColor::WHITE: {
                    switch (piece_type) {
                        case libchess::PieceType::PAWN:
                            sprite = &_sprites.GetWhitePawnSprite();
                            break;
                        case libchess::PieceType::KNIGHT:
                            sprite = &_sprites.GetWhiteKnightSprite();
                            break;
                        case libchess::PieceType::BISHOP:
                            sprite = &_sprites.GetWhiteBishopSprite();
                            break;
                        case libchess::PieceType::ROOK:
                            sprite = &_sprites.GetWhiteRookSprite();
                            break;
                        case libchess::PieceType::QUEEN:
                            sprite = &_sprites.GetWhiteQueenSprite();
                            break;
                        case libchess::PieceType::KING: {
                            sprite = &_sprites.GetWhiteKingSprite();
                            break;
                        }
                    }
                    break;
                }
            }

            if (sprite == nullptr) {
                continue;
            }

            sprite->setPosition(position);
            window.draw(*sprite);
        }
    }
}

sf::Vector2i Game::WindowClickPositionToSquare(int x, int y) {
    return sf::Vector2i(static_cast<int>((x - kTopLeftPadding) / _square_width),
                        static_cast<int>((y - kTopLeftPadding) / _square_width));
}
