#include <SFML/Graphics.hpp>
#include <vector>

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
inline const sf::RectangleShape& WOOD() {
    static const sf::RectangleShape instance = createBlock("wood");
    return instance;
}
inline sf::RectangleShape WOOD(sf::Vector2f pos) {
    sf::RectangleShape rect = WOOD();
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

    std::vector<Block> placedBlocks;
    Block block;
    int selected_block_type = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseClick->position);
                    sf::Vector2f gridPos = getGridPos(mousePos);

                    sf::Vector2f finalPos = {gridPos.x + 10.f, gridPos.y + 10.f};

                    block.pos = finalPos;
                    block.type = static_cast<BlockType>(selected_block_type);

                    placedBlocks.push_back(block);
                }
            } else if (const auto* keyClick = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyClick->code) {
                    case sf::Keyboard::Key::Num1:
                        selected_block_type = 0; // Iron
                        break;
                    case sf::Keyboard::Key::Num2:
                        selected_block_type = 1; // Wood
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear(sf::Color::Black);

        for (const auto& block : placedBlocks) {
            switch (block.type) {
                case BlockType::Iron:
                    window.draw(Blocks::IRON(block.pos));
                    break;
                case BlockType::Wood:
                    window.draw(Blocks::WOOD(block.pos));
                    break;
            }
        }

        window.display();
    }
}
