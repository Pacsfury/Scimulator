#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>

#include "../include/blocks.hpp"
#include "../include/grid.hpp"
#include "../include/propiertiesdsl/lexer.hpp"

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

std::string valString(auto value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, std::string>) {
        return std::string(value);
    } else if constexpr (std::is_same_v<T, bool>) {
        return std::string(value ? "true" : "false");
    } else if constexpr (std::is_same_v<T, int>) {
        return std::to_string(value);
    } else if constexpr (std::is_same_v<T, float>) {
        return std::to_string(value);
    }
    return std::string{};
}

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Scimulator");
    window.setVerticalSyncEnabled(true);

    sf::View view;
    view.setSize({1920.f, 1080.f});
    view.setCenter({0.f, 0.f});
    window.setView(view);

    bool isFullscreen = false;
    sf::String currentTitle = "Scimulator";

    std::ifstream env(
        ".simdata/env.p");  // .simdata/env.p contains things such as floor? gravity. air-density. project_, etc
    std::stringstream buffer;
    buffer << env.rdbuf();
    auto envPropierties = lex(buffer.str());

    const auto valueToString = [](const auto& value) { return valString(value); };

    unsigned int targetWidth = 1920;
    unsigned int targetheigth = 1080;
    bool shouldResize = false;

    for (Node n : envPropierties) {
        if (n.key == "project") {
            const std::string nameString = std::visit(valueToString, n.value) + " @ Scimulator";
            currentTitle = sf::String::fromUtf8(nameString.begin(), nameString.end());
            window.setTitle(currentTitle);
        } else if (n.key == "heigth") {
            const std::string heigthStr = std::visit(valueToString, n.value);
            targetheigth = static_cast<unsigned int>(std::atoi(heigthStr.c_str()));
            shouldResize = true;
        } else if (n.key == "width") {
            const std::string widthStr = std::visit(valueToString, n.value);
            targetWidth = static_cast<unsigned int>(std::atoi(widthStr.c_str()));
            shouldResize = true;
        } else if (n.key == "full") {
            isFullscreen = !isFullscreen;
            const std::string val = std::visit(valueToString, n.value);

            if (isFullscreen && val == "true") {
                sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
                window.create(desktopMode, currentTitle, sf::State::Fullscreen);
            } else {
                window.create(sf::VideoMode(window.getSize()), currentTitle, sf::State::Windowed);
            }
        }
    }

    if (shouldResize) {
        window.setSize({targetWidth, targetheigth});

        view.setSize({static_cast<float>(targetWidth), static_cast<float>(targetheigth)});
        window.setView(view);
    }
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
                        selected_block_type = 0;  // Iron
                        break;
                    case sf::Keyboard::Key::Num2:
                        selected_block_type = 1;  // Wood
                        break;
                    case sf::Keyboard::Key::F11:
                        isFullscreen = !isFullscreen;
                        if (isFullscreen) {
                            sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
                            window.create(desktopMode, currentTitle, sf::State::Fullscreen);
                        } else {
                            window.create(sf::VideoMode({targetWidth, targetheigth}), currentTitle,
                                          sf::State::Windowed);
                        }

                        window.setVerticalSyncEnabled(true);
                        window.setView(view);
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
