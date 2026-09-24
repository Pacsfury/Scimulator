#include <SFML/Graphics.hpp>
#include <cmath>

#include "../include/grid.hpp"

sf::Vector2f getGridPos(sf::Vector2f m) {
    float gridX = (float)static_cast<int>(std::floor(m.x / 60.f)) * 60;
    float gridY = (float)static_cast<int>(std::floor(m.y / 60.f)) * 60;

    return {gridX, gridY};
}