#include "Headers/Assets/GameAssets.h"
#include <SFML/Graphics/RenderWindow.hpp>

GameAssets::GameAssets(float width, float height)
{
    this->width = width;
    this->height = height;
}

void GameAssets::draw(sf::RenderWindow& window)
{
    for (const auto& i : Assets)
        window.draw(i);
}
