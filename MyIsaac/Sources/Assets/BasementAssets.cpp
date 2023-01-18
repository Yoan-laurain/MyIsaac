#include "Headers/Assets//BasementAssets.h"
#include "Headers/Managers/TextureMgr.h"

BasementAssets::BasementAssets(const float width, const float height): GameAssets( width, height)
{
    TextureMgr::Instance()->parse_basements("./Ressources/Basement");
    FullBasement = &TextureMgr::Instance()->get_texture("./Ressources/Basement.png");
    spriteBasement = new sf::Sprite(*FullBasement);
    this->width = width;
    this->height = height;
}

void BasementAssets::draw(sf::RenderWindow& window)
{
    GameAssets::draw(window);
}

void BasementAssets::LoadAssets()
{
    int cmpt_left_wall = 0;
    int cmpt_right_wall = 0;
    int cmpt_top_wall = 0;
    int cmpt_bottom_wall = 0;
    
    for ( int i = 0; i < 12; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallLeft = TextureMgr::Instance()->map["Wall_Classic_Left"];
            
            spriteBasement->setTextureRect(sf::IntRect(static_cast<int>(wallLeft.x), static_cast<int>(wallLeft.y),
                                                       static_cast<int>(wallLeft.SizeX),
                                                       static_cast<int>(wallLeft.SizeY)));
            spriteBasement->setScale(2.f, 2.f);
            spriteBasement->setPosition(- 26, static_cast<float>(104 * cmpt_left_wall+1 + 78));
            
            cmpt_left_wall++;
        }
        else
        {
            my_struct wallRight = TextureMgr::Instance()->map["Wall_Classic_Right"];
            
            spriteBasement->setTextureRect(sf::IntRect(static_cast<int>(wallRight.x), static_cast<int>(wallRight.y),
                                                       static_cast<int>(wallRight.SizeX),
                                                       static_cast<int>(wallRight.SizeY)));
            
            spriteBasement->setScale(-2.f, 2.f);
            spriteBasement->setPosition(width + 26 , static_cast<float>(104 * cmpt_right_wall+1 + 78) );
            
            cmpt_right_wall++;
        }

        Assets.push_back(*spriteBasement);
    }

    for ( int i = 0; i < 22; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallUp = TextureMgr::Instance()->map["Wall_Classic_Up"];
            
            spriteBasement->setTextureRect(sf::IntRect(static_cast<int>(wallUp.x), static_cast<int>(wallUp.y),
                                                       static_cast<int>(wallUp.SizeX), static_cast<int>(wallUp.SizeY)));

            spriteBasement->setScale(2.f, 2.f);
            spriteBasement->setPosition(static_cast<float>(104 * cmpt_top_wall+1 +78), -26);
            
            cmpt_top_wall++;
        }
        else
        {
            my_struct wall_down = TextureMgr::Instance()->map["Wall_Classic_Down"];
            
            spriteBasement->setTextureRect(sf::IntRect(static_cast<int>(wall_down.x), static_cast<int>(wall_down.y),
                                                       static_cast<int>(wall_down.SizeX),
                                                       static_cast<int>(wall_down.SizeY)));
            
            spriteBasement->setScale(2.f, -2.f);
            spriteBasement->setPosition(static_cast<float>(104 * cmpt_bottom_wall+1 + 78), height + 26);
            
            cmpt_bottom_wall++;
        }
        Assets.push_back(*spriteBasement);
    }

    for ( int i = 1; i < 7; i++)
    {
        my_struct ground = TextureMgr::Instance()->map["Ground_Line_Up"];
        
        spriteBasement->setTextureRect(sf::IntRect(static_cast<int>(ground.x), static_cast<int>(ground.y),
                                                   static_cast<int>(ground.SizeX), static_cast<int>(ground.SizeY)));
        
        spriteBasement->setScale(1144.f / 676, 2);
        spriteBasement->setPosition(78, static_cast<float>(i * 104 - 24));
        
        Assets.push_back(*spriteBasement);
    }
}

void BasementAssets::load_corner()
{
    sf::Sprite sprite_corner_top_left(*FullBasement);
    my_struct corner_top_left = TextureMgr::Instance()->map["Corner_Top_Left"];
    sprite_corner_top_left.setTextureRect(sf::IntRect(static_cast<int>(corner_top_left.x), static_cast<int>(corner_top_left.y),
                                                   static_cast<int>(corner_top_left.SizeX),
                                                   static_cast<int>(corner_top_left.SizeY)));

    sprite_corner_top_left.setScale(2.f, 2.f);
    sprite_corner_top_left.setPosition(-corner_top_left.SizeX /2 , -corner_top_left.SizeY /2);

    //

    sf::Sprite sprite_corner_top_right(*FullBasement);
    my_struct corner_top_right = TextureMgr::Instance()->map["Corner_Top_Right"];
    sprite_corner_top_right.setTextureRect(sf::IntRect(static_cast<int>(corner_top_right.x),
                                                    static_cast<int>(corner_top_right.y),
                                                    static_cast<int>(corner_top_right.SizeX),
                                                    static_cast<int>(corner_top_right.SizeY)));
    
    sprite_corner_top_right.setScale(-2.f, 2.f);

    sprite_corner_top_right.setPosition(width + corner_top_right.SizeX / 2 , -corner_top_right.SizeY / 2);

    //

    sf::Sprite sprite_corner_bottom_left(*FullBasement);
    my_struct corner_bottom_left = TextureMgr::Instance()->map["Corner_Bottom_Left"];
    sprite_corner_bottom_left.setTextureRect(sf::IntRect(static_cast<int>(corner_bottom_left.x),
                                                      static_cast<int>(corner_bottom_left.y),
                                                      static_cast<int>(corner_bottom_left.SizeX),
                                                      static_cast<int>(corner_bottom_left.SizeY)));

    sprite_corner_bottom_left.setScale(2.f, -2.f);
    sprite_corner_bottom_left.setPosition(-corner_bottom_left.SizeX / 2,height + corner_bottom_left.SizeY / 2);

    // 

    sf::Sprite sprite_corner_bottom_right(*FullBasement);
    my_struct corner_bottom_right = TextureMgr::Instance()->map["Corner_Bottom_Right"];
    sprite_corner_bottom_right.setTextureRect(sf::IntRect(static_cast<int>(corner_bottom_right.x),
                                                       static_cast<int>(corner_bottom_right.y),
                                                       static_cast<int>(corner_bottom_right.SizeX),
                                                       static_cast<int>(corner_bottom_right.SizeY)));

    sprite_corner_bottom_right.setScale(-2.f, -2.f);
    sprite_corner_bottom_right.setPosition(width + corner_bottom_right.SizeX / 2,height + corner_bottom_right.SizeY / 2);

    Assets.push_back(sprite_corner_top_left);
    Assets.push_back(sprite_corner_top_right);
    Assets.push_back(sprite_corner_bottom_left);
    Assets.push_back(sprite_corner_bottom_right);
}

