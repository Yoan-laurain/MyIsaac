#pragma once
#include "GameAssets.h"

class BasementAssets : public GameAssets
{

    public:
        BasementAssets(float width, float height);

        void draw(sf::RenderWindow& window) override;
        void LoadAssets();
        void load_corner();
    
        sf::Texture* FullBasement;
        sf::Sprite* spriteBasement;
};
