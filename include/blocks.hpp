#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <format>

enum class BlockType {
    Iron, Wood
};

struct Block {
    BlockType type;
    sf::Vector2f pos;
};


sf::RectangleShape createBlock(const std::string& name, sf::Vector2f pos = {0.f, 0.f});