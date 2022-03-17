#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <libchess/board.h>
#include <libchess/piece.h>

#include "game.h"

constexpr unsigned int kWindowWidth = 800;
constexpr unsigned int kFramerate = 30;

int main() {
    game game(kWindowWidth);

    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowWidth),
                            "libchess demo",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(kFramerate);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                game.on_click(event.mouseButton.x, event.mouseButton.y);
            }
        }

        window.clear(sf::Color(sf::Color::White));

        game.draw(window);

        window.display();
    }

    return 0;
}
