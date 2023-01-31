#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "IDrawable.h"

class MyRect : public IDrawable
{
    public:
        MyRect();
        ~MyRect() override;
    
        void init() override;
        void update() override;
        void destroy() override;
    
        void set_color( sf::Color color );
        void set_size( sf::Vector2f size );

    private:
        sf::RectangleShape* m_rect;
        
};
