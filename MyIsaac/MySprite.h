#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "IDrawable.h"
#include "Transform.h"

class MySprite : public IDrawable
{
    public:
        MySprite();
        ~MySprite() override;

        void init() override;
        void update() override;
        void destroy() override;
    
        sf::Drawable& get_drawable() override;

    private:
        std::string nom;
        Transform* m_transform;
        sf::Sprite* m_sprite;
};
