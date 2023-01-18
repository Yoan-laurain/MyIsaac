#pragma once
#include "GameAssets.h"
#include "../Managers/TextureMgr.h"

class TearAssets : public GameAssets
{

    public:
        TearAssets(float width, float height);

        void draw(sf::RenderWindow& window, std::vector<my_struct> tears);

        sf::Texture* Tear;
        sf::Sprite* spriteTear;
};
