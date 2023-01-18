#include "Headers/BasementAssets.h"

BasementAssets::BasementAssets(float width, float height): GameAssets( width, height)
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
    int cmptLeftWall = 0;
    int cmptRightWall = 0;
    int cmptTopWall = 0;
    int cmptBottomWall = 0;
    
    for ( int i = 0; i < 12; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallLeft = TextureMgr::Instance()->map["Wall_Classic_Left"];
            
            spriteBasement->setTextureRect(sf::IntRect(wallLeft.x, wallLeft.y, wallLeft.SizeX, wallLeft.SizeY));
            spriteBasement->setScale(2.f, 2.f);
            spriteBasement->setPosition(- 26, 104 * cmptLeftWall+1 + 78);
            
            cmptLeftWall++;
        }
        else
        {
            my_struct wallRight = TextureMgr::Instance()->map["Wall_Classic_Right"];
            
            spriteBasement->setTextureRect(sf::IntRect(wallRight.x, wallRight.y, wallRight.SizeX, wallRight.SizeY));
            spriteBasement->setScale(-2.f, 2.f);
            spriteBasement->setPosition(width + 26 , 104 * cmptRightWall+1 + 78 );
            
            cmptRightWall++;
        }

        Assets.push_back(*spriteBasement);
    }

    for ( int i = 0; i < 22; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallUp = TextureMgr::Instance()->map["Wall_Classic_Up"];
            
            spriteBasement->setTextureRect(sf::IntRect(wallUp.x, wallUp.y, wallUp.SizeX, wallUp.SizeY));
            spriteBasement->setScale(2.f, 2.f);
            spriteBasement->setPosition(104 * cmptTopWall+1 +78, -26);
            
            cmptTopWall++;
        }
        else
        {
            my_struct wall_down = TextureMgr::Instance()->map["Wall_Classic_Down"];
            
            spriteBasement->setTextureRect(sf::IntRect(wall_down.x, wall_down.y, wall_down.SizeX, wall_down.SizeY));
            spriteBasement->setScale(2.f, -2.f);
            spriteBasement->setPosition(104 * cmptBottomWall+1 + 78, height + 26);
            
            cmptBottomWall++;
        }
        Assets.push_back(*spriteBasement);
    }

    for ( int i = 1; i < 7; i++)
    {
        my_struct ground = TextureMgr::Instance()->map["Ground_Line_Up"];
        
        spriteBasement->setTextureRect(sf::IntRect(ground.x, ground.y, ground.SizeX, ground.SizeY));
        spriteBasement->setScale(1144.f / 676, 2);
        spriteBasement->setPosition(78, i * 104 - 24);
        
        Assets.push_back(*spriteBasement);
    }
}

void BasementAssets::load_corner()
{
    sf::Sprite spriteCornerTopLeft(*FullBasement);
    my_struct cornerTopLeft = TextureMgr::Instance()->map["Corner_Top_Left"];
    spriteCornerTopLeft.setTextureRect(sf::IntRect(cornerTopLeft.x, cornerTopLeft.y, cornerTopLeft.SizeX, cornerTopLeft.SizeY));

    spriteCornerTopLeft.setScale(2.f, 2.f);
    spriteCornerTopLeft.setPosition(-cornerTopLeft.SizeX /2 , -cornerTopLeft.SizeY /2);

    //

    sf::Sprite spriteCornerTopRight(*FullBasement);
    my_struct cornerTopRight = TextureMgr::Instance()->map["Corner_Top_Right"];
    spriteCornerTopRight.setTextureRect(sf::IntRect(cornerTopRight.x, cornerTopRight.y, cornerTopRight.SizeX, cornerTopRight.SizeY));
    
    spriteCornerTopRight.setScale(-2.f, 2.f);

    spriteCornerTopRight.setPosition(width + cornerTopRight.SizeX / 2 , -cornerTopRight.SizeY / 2);

    //

    sf::Sprite spriteCornerBottomLeft(*FullBasement);
    my_struct cornerBottomLeft = TextureMgr::Instance()->map["Corner_Bottom_Left"];
    spriteCornerBottomLeft.setTextureRect(sf::IntRect(cornerBottomLeft.x, cornerBottomLeft.y, cornerBottomLeft.SizeX, cornerBottomLeft.SizeY));

    spriteCornerBottomLeft.setScale(2.f, -2.f);
    spriteCornerBottomLeft.setPosition(-cornerBottomLeft.SizeX / 2,height + cornerBottomLeft.SizeY / 2);

    // 

    sf::Sprite spriteCornerBottomRight(*FullBasement);
    my_struct cornerBottomRight = TextureMgr::Instance()->map["Corner_Bottom_Right"];
    spriteCornerBottomRight.setTextureRect(sf::IntRect(cornerBottomRight.x, cornerBottomRight.y, cornerBottomRight.SizeX, cornerBottomRight.SizeY));

    spriteCornerBottomRight.setScale(-2.f, -2.f);
    spriteCornerBottomRight.setPosition(width + cornerBottomRight.SizeX / 2,height + cornerBottomRight.SizeY / 2);

    Assets.push_back(spriteCornerTopLeft);
    Assets.push_back(spriteCornerTopRight);
    Assets.push_back(spriteCornerBottomLeft);
    Assets.push_back(spriteCornerBottomRight);
}

