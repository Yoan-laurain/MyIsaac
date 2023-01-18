#include "Headers/IsaacAssets.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Headers/GameDatas.h"

IsaacAssets::IsaacAssets(float width, float height) : GameAssets ( width, height )
{
    TextureMgr::Instance()->parseAnimations("../Ressources/IsaacSprite");
    FullAnimations = &TextureMgr::Instance()->get_texture("../Ressources/IsaacSprite.png");

    this->width = width;
    this->height = height;
}

void IsaacAssets::draw(sf::RenderWindow& window)
{
    GameAssets::draw(window);
}

void IsaacAssets::load_assets()
{
    spriteHead = new sf::Sprite(*FullAnimations);
    spriteBody = new sf::Sprite(*FullAnimations);
    
    spriteHead->setScale(2.f, 2.f);
    spriteBody->setScale(2.f, 2.f);
    
    std::vector<std::string> animations = {"Head_Up","Head_Right","Head_Down","Head_Left","Body_Vertical","Body_Right","Body_Left"};;
    sf::Sprite anim(*FullAnimations);
    
    for ( int i = 0 ; i < 7 ; i++ )
    {
        my_struct texture = TextureMgr::Instance()->map[animations[i]];
        
        anim.setScale(2.f, 2.f);
    
        anim.setTextureRect(sf::IntRect(texture.x, texture.y, texture.SizeX, texture.SizeY));
        animationsSprite.push_back( new sf::Sprite(anim) );
    }
}

void IsaacAssets::update(sf::RenderWindow& window)
{
    spriteHead = animationsSprite[WhichAnimations(true)];
    spriteBody = animationsSprite[WhichAnimations(false)];

    my_struct head = TextureMgr::Instance()->map["Head_Down"];
    my_struct body = TextureMgr::Instance()->map["Body_Vertical"];
            
    // Display player 
    spriteHead->setPosition(GameDatas::Instance()->xPlayer, GameDatas::Instance()->yPlayer);
    spriteBody->setPosition(GameDatas::Instance()->xPlayer, GameDatas::Instance()->yPlayer + head.SizeY * 1.2);

    // set the image at the center of the sprite
    spriteHead->setOrigin(head.SizeX / 2, head.SizeY / 2);
    spriteBody->setOrigin(body.SizeX / 2, body.SizeY / 2);

    window.draw(*spriteHead);
    window.draw(*spriteBody);
}

int IsaacAssets::WhichAnimations(bool head)
{
    if ( head)
    {
        switch (GameDatas::Instance()->currentAction)
        {
            case GameDatas::Up:
                return 0;
            case GameDatas::Right:
                return 1;
            case GameDatas::Down:
                return 2;
            case GameDatas::Left:
                return 3;
        }
        return 2;
    }
    else
    {
        switch (GameDatas::Instance()->currentAction)
        {
            case GameDatas::Up:
                return 4;
            case GameDatas::Right:
                return 5;
            case GameDatas::Down:
                return 4;
            case GameDatas::Left:
                return 6;
        }
        return 4;
    }
}

