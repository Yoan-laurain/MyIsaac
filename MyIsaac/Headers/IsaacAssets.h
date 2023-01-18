#pragma once
#include "GameAssets.h"

class IsaacAssets: public GameAssets
{
    public:

        IsaacAssets(float width, float height);

        void draw(sf::RenderWindow& window) override;
        void load_assets();
        void update(sf::RenderWindow& window);
        int WhichAnimations(bool head = true);

        sf::Texture* FullAnimations;
        std::vector<sf::Sprite*> animationsSprite;

        sf::Sprite* spriteHead;
        sf::Sprite* spriteBody;
    
};
