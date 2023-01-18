#include "Headers/Assets/TearAssets.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Headers/Managers/TextureMgr.h"

TearAssets::TearAssets(float width, float height) : GameAssets ( width, height )
{
    TextureMgr::Instance()->parseAnimations("../Ressources/Tear");
    Tear = &TextureMgr::Instance()->get_texture("../Ressources/Tear.png");
    spriteTear = new sf::Sprite(*Tear);

    this->width = width;
    this->height = height;
    
    my_struct tear = TextureMgr::Instance()->map["Default_Tear"];
    spriteTear->setTextureRect(sf::IntRect(tear.x, tear.y, tear.SizeX, tear.SizeY));
    spriteTear->setScale(2.f, 2.f);
}

void TearAssets::draw(sf::RenderWindow& window, std::vector<my_struct> tears)
{
    for (int i = 0; i < tears.size(); i++)
    {
        spriteTear->setPosition(tears[i].x, tears[i].y);
        window.draw(*spriteTear);
    }
}