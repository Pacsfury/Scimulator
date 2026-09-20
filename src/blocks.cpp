#include <SFML/Graphics.hpp>
#include <format>
#include <string>
#include <unordered_map>

#include "../include/blocks.hpp"

sf::RectangleShape createBlock(const std::string& name, sf::Vector2f pos) {
    static std::unordered_map<std::string, sf::Texture> textureCache;

    auto [it, inserted] = textureCache.try_emplace(name);

    if (inserted) {
        if (!it->second.loadFromFile(std::format("assets/images/{}.png", name))) {
        }
    }

    const sf::Texture& rectT = it->second;

    sf::Vector2f size{static_cast<float>(rectT.getSize().x), static_cast<float>(rectT.getSize().y)};

    sf::RectangleShape rect(size);
    rect.setTexture(&rectT);
    
    rect.setOrigin(size / 2.0f);
    
    rect.setPosition(pos);
    rect.setScale({0.2f, 0.2f});
    
    return rect;
}
