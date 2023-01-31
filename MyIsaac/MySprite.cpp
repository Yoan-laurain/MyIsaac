#include "MySprite.h"

#include "Headers/Managers/TextureMgr.h"

MySprite::MySprite(): m_transform(nullptr), m_sprite(nullptr)
{
    m_sprite = new sf::Sprite();
}

MySprite::~MySprite() {}

void MySprite::init()
{
    m_sprite->setPosition(m_transform->getPosition());
    m_sprite->setTexture(TextureMgr::Instance()->get_texture(""));
}

void MySprite::update()
{
    m_sprite->setPosition(m_transform->getPosition());
}

void MySprite::destroy()
{

}

sf::Drawable& MySprite::get_drawable()
{
    return *m_sprite;
}
