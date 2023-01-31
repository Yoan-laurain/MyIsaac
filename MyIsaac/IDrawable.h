#pragma once
#include "Transform.h"

namespace sf
{
    class Sprite;
}

class IDrawable abstract
{
    public:

        IDrawable() {}
        virtual ~IDrawable() {}

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;
        virtual sf::Drawable& get_drawable() = 0;

    private :
        sf::Drawable* m_drawable;
        
};
