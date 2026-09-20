#include <SFML/Graphics.hpp>
#include <vector>  // Necesario para guardar las posiciones de los bloques

#include "../include/blocks.hpp"
#include "../include/grid.hpp"

namespace Blocks {
inline const sf::RectangleShape& IRON() {
    static const sf::RectangleShape instance = createBlock("iron");
    return instance;
}
inline sf::RectangleShape IRON(sf::Vector2f pos) {
    sf::RectangleShape rect = IRON();
    rect.setPosition(pos);
    return rect;
}
}  // namespace Blocks

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Simulator");
    window.setVerticalSyncEnabled(true);

    sf::View view;
    view.setSize({1920.f, 1080.f});
    view.setCenter({0.f, 0.f});
    window.setView(view);

    std::vector<sf::Vector2f> placedBlocks;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseClick->position);
                    sf::Vector2f gridPos = getGridPos(mousePos);

                    sf::Vector2f finalPos = {gridPos.x + 10.f, gridPos.y + 10.f};

                    placedBlocks.push_back(finalPos);
                }
            }
        }

        window.clear(sf::Color::Black);

        for (const auto& pos : placedBlocks) {
            window.draw(Blocks::IRON(pos));
        }

        window.display();
    }
}
