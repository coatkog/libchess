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
#include <sstream>

#define log(x) std::cout << x << std::endl

const sf::Color Game::kWhiteSquareColor = sf::Color::White;
const sf::Color Game::kBlackSquareColor = sf::Color(128, 128, 128);
const sf::Color Game::kSelectedSquareColor = sf::Color::Red;
const sf::Color Game::kAvailableSquareColor = sf::Color(192, 192, 192);

Game::Game(float width)
    : m_width(width)
    , m_board_width(width - kTopLeftPadding - kBottomRightPadding)
    , m_square_width((width - kTopLeftPadding - kBottomRightPadding) / 8)
    , m_sprites(m_square_width)
    , m_clicked_square(-1, -1) {
    m_sprites.Create();

    if (!m_font.loadFromFile("../demo-gui/assets/ClearSans-Regular.ttf")) {
        // TODO:
    }
}

void Game::Draw(sf::RenderWindow& window) {
    DrawBoard(window);
    DrawBoardInfo(window);
    DrawLogs(window);
    DrawPieces(window);

    DrawAvailableMoves(window);
}

void Game::OnClick(int x, int y) {
    if (x < kTopLeftPadding || x > kTopLeftPadding + m_board_width) {
        return;
    }
    if (y < kTopLeftPadding || y > kTopLeftPadding + m_board_width) {
        return;
    }

    if (m_clicked_square.x != -1) {
        sf::Vector2i new_clicked_square = WindowClickPositionToSquare(x, y);

        DoMove(m_clicked_square.x, m_clicked_square.y, new_clicked_square.x, new_clicked_square.y);

        m_clicked_square.x = -1;
        m_clicked_square.y = -1;
    } else {
        m_clicked_square = WindowClickPositionToSquare(x, y);

        auto start = std::chrono::steady_clock::now();

        m_available_moves = m_board.GetAvailableMoves(m_clicked_square.x, m_clicked_square.y);

        auto end = std::chrono::steady_clock::now();

        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        m_logs.emplace_back("Took: " + std::to_string(delta) + " ns to calculate available moves.");
        log("Took: " << delta << " ns to calculate available moves.");
    }
}

void Game::DoMove(int starting_x, int starting_y, int ending_x, int ending_y) {
    try {
        m_board.DoMove(starting_x, starting_y, ending_x, ending_y);
    } catch (const std::exception& e) {
        m_logs.emplace_back("Error: " + std::string(e.what()));
        log("Error: " << e.what());
    }
}

void Game::DrawAvailableMoves(sf::RenderWindow& window) {
    if (m_clicked_square.x == -1) {
        return;
    }

    sf::CircleShape dot(kAvailableMoveCircleRadius);
    dot.setFillColor(kAvailableSquareColor);

    for (const auto& move : m_available_moves) {
        int ending_x = move.GetEndingX();
        int ending_y = move.GetEndingY();

        dot.setPosition(sf::Vector2f(kTopLeftPadding + ending_x * m_square_width +
                                         m_square_width / 2 - kAvailableMoveCircleRadius,
                                     kTopLeftPadding + ending_y * m_square_width +
                                         m_square_width / 2 - kAvailableMoveCircleRadius));

        window.draw(dot);
    }
}

void Game::DrawBoard(sf::RenderWindow& window) {
    sf::RectangleShape board(sf::Vector2f(m_board_width, m_board_width));
    board.setOutlineThickness(2);
    board.setOutlineColor(sf::Color::Black);
    board.setPosition(sf::Vector2f(kTopLeftPadding, kTopLeftPadding));

    window.draw(board);

    for (std::size_t i = 0; i < 8; i++) {
        for (std::size_t j = 0; j < 8; j++) {
            libchess::Square square = m_board.GetBoard()[i][j];

            sf::RectangleShape square_shape(sf::Vector2f(m_square_width, m_square_width));

            if (m_clicked_square.x == static_cast<int>(j) &&
                m_clicked_square.y == static_cast<int>(i)) {
                square_shape.setFillColor(kSelectedSquareColor);
            } else {
                if (square.GetColor() == libchess::SquareColor::WHITE) {
                    square_shape.setFillColor(kWhiteSquareColor);
                } else {
                    square_shape.setFillColor(kBlackSquareColor);
                }
            }

            square_shape.setPosition(sf::Vector2f(kTopLeftPadding + j * m_square_width,
                                                  kTopLeftPadding + i * m_square_width));

            window.draw(square_shape);
        }
    }
}

void Game::DrawBoardInfo(sf::RenderWindow& window) {
    for (std::size_t i = 0; i < 8; i++) {
        sf::Text text;
        text.setFont(m_font);
        text.setFillColor(sf::Color::Black);

        float char_size = m_width / 50;
        text.setCharacterSize(char_size);

        text.setString(static_cast<char>('A' + i));
        text.setPosition(
            sf::Vector2f(kTopLeftPadding + m_square_width / 2 + i * m_square_width - char_size / 2,
                         m_width - kBottomRightPadding / 2 - char_size / 2));
        window.draw(text);

        text.setString(static_cast<char>('8' - i));
        text.setPosition(
            sf::Vector2f(m_width - kBottomRightPadding / 2 - char_size / 2,
                         kTopLeftPadding + m_square_width / 2 + i * m_square_width - char_size / 2));
        window.draw(text);
    }
}

void Game::DrawLogs(sf::RenderWindow& window) {
    int count = 1;
    for (const std::string& l : m_logs) {
        sf::Text text;
        text.setFont(m_font);
        text.setFillColor(sf::Color::Black);

        float char_size = m_width / 50;
        text.setCharacterSize(char_size);

        text.setString(l);
        text.setPosition(sf::Vector2f(m_width + kTopLeftPadding,
                                      kTopLeftPadding + count++ * kLogsSpacing));
        window.draw(text);
    }
}

void Game::DrawPieces(sf::RenderWindow& window) {
    for (std::size_t i = 0; i < 8; i++) {
        for (std::size_t j = 0; j < 8; j++) {
            libchess::Square square = m_board.GetBoard()[i][j];

            if (square.Empty()) {
                continue;
            }

            sf::Sprite* sprite = nullptr;

            libchess::PieceColor piece_color = square.GetPieceColor();
            libchess::PieceType piece_type = square.GetPieceType();

            switch (piece_color) {
                case libchess::PieceColor::BLACK: {
                    switch (piece_type) {
                        case libchess::PieceType::PAWN:
                            sprite = &m_sprites.GetBlackPawnSprite();
                            break;
                        case libchess::PieceType::KNIGHT:
                            sprite = &m_sprites.GetBlackKnightSprite();
                            break;
                        case libchess::PieceType::BISHOP:
                            sprite = &m_sprites.GetBlackBishopSprite();
                            break;
                        case libchess::PieceType::ROOK:
                            sprite = &m_sprites.GetBlackRookSprite();
                            break;
                        case libchess::PieceType::QUEEN:
                            sprite = &m_sprites.GetBlackQueenSprite();
                            break;
                        case libchess::PieceType::KING:
                            sprite = &m_sprites.GetBlackKingSprite();
                            break;
                    }
                    break;
                }
                case libchess::PieceColor::WHITE: {
                    switch (piece_type) {
                        case libchess::PieceType::PAWN:
                            sprite = &m_sprites.GetWhitePawnSprite();
                            break;
                        case libchess::PieceType::KNIGHT:
                            sprite = &m_sprites.GetWhiteKnightSprite();
                            break;
                        case libchess::PieceType::BISHOP:
                            sprite = &m_sprites.GetWhiteBishopSprite();
                            break;
                        case libchess::PieceType::ROOK:
                            sprite = &m_sprites.GetWhiteRookSprite();
                            break;
                        case libchess::PieceType::QUEEN:
                            sprite = &m_sprites.GetWhiteQueenSprite();
                            break;
                        case libchess::PieceType::KING: {
                            sprite = &m_sprites.GetWhiteKingSprite();
                            break;
                        }
                    }
                    break;
                }
            }

            if (sprite == nullptr) {
                continue;
            }

            sprite->setPosition(sf::Vector2f(kTopLeftPadding + j * m_square_width,
                                             kTopLeftPadding + i * m_square_width));
            window.draw(*sprite);
        }
    }
}

sf::Vector2i Game::WindowClickPositionToSquare(int x, int y) {
    return sf::Vector2i(static_cast<int>((x - kTopLeftPadding) / m_square_width),
                        static_cast<int>((y - kTopLeftPadding) / m_square_width));
}
