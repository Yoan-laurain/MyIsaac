#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

#include "TextureMgr.h"

namespace sf
{
    class RenderWindow;
}

class GameAssets
{
public :
    
    GameAssets(float width, float height);

    virtual void draw(sf::RenderWindow& window);
    
    std::vector<sf::Sprite> Assets;
    
    float width;
    float height;
};
