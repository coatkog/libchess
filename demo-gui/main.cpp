#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <libchess/board.h>
#include <libchess/piece.h>

#include "game.h"

#include <iostream>
#include <memory>

#define WINDOW_WIDTH           800
#define WINDOW_WIDTH_WITH_LOGS WINDOW_WIDTH + 400
#define FRAMERATE              30

int main() {
    Game game(WINDOW_WIDTH);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH_WITH_LOGS, WINDOW_WIDTH),
                            "libchess demo",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                game.OnClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        window.clear(sf::Color(sf::Color::White));

        game.Draw(window);

        window.display();
    }

    return 0;
}