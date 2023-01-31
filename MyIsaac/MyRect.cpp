#include "MyRect.h"

MyRect::MyRect() {}

MyRect::~MyRect() {}

void MyRect::init()
{
    m_rect = new sf::RectangleShape();
    m_rect->setFillColor(sf::Color::Red);
    m_rect->setSize(sf::Vector2f(100, 100));
}

void MyRect::update() {}

void MyRect::destroy() {}

void MyRect::set_color(sf::Color color)
{
    m_rect->setFillColor(color);
}

void MyRect::set_size(sf::Vector2f size)
{
    m_rect->setSize(size);
}
