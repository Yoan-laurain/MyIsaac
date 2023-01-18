#include "Headers/GameDatas.h"
#include "Headers/Managers/InputManager.h"
#include "Headers/Assets/TearAssets.h"
#include "Headers/Managers/TextureMgr.h"

struct my_struct;
GameDatas *GameDatas::pInstance = nullptr;

GameDatas::GameDatas()
{
    height = 780;
    width = 1300;
    SpeedPlayer = 0.3f;
    ball_speed = 0.35f;

    InputManager::Instance()->BindKey(Enums::Up, sf::Keyboard::Z);
    InputManager::Instance()->BindKey(Enums::Down, sf::Keyboard::S);
    InputManager::Instance()->BindKey(Enums::Left, sf::Keyboard::Q);
    InputManager::Instance()->BindKey(Enums::Right, sf::Keyboard::D);
    InputManager::Instance()->BindKey(Enums::Exit, sf::Keyboard::Escape);
    InputManager::Instance()->BindKey(Enums::Shoot, sf::Keyboard::Space);

    xPlayer  = width / 2;
    yPlayer  = height / 2;

    tearAssets = new TearAssets(width,height);
}

GameDatas* GameDatas::Instance()
{
    if (pInstance == nullptr)
        pInstance = new GameDatas;

    return pInstance;
}

int GameDatas::update(sf::RenderWindow &window)
{
    if(InputManager::Instance()->KeyDown(Enums::Up))
    {
        Instance()->yPlayer = ( yPlayer < 120  ? 120  : Instance()->yPlayer  -= SpeedPlayer );
        Instance()->currentAction = Enums::Up;
    }
    
    if(InputManager::Instance()->KeyDown(Enums::Down))
    {
        Instance()->yPlayer  = ( Instance()->yPlayer   > height - 120 ? height - 120 : Instance()->yPlayer  += SpeedPlayer );
        Instance()->currentAction = Enums::Down;
    }

    if(InputManager::Instance()->KeyDown(Enums::Left))
    {
        Instance()->xPlayer  = ( Instance()->xPlayer  < 120 ? 120 : Instance()->xPlayer  -= SpeedPlayer );
        Instance()->currentAction = Enums::Left;
    }
    
    if(InputManager::Instance()->KeyDown(Enums::Right))
    {
        Instance()->xPlayer  = ( Instance()->xPlayer   > width - 120 ? width - 120 : Instance()->xPlayer  += SpeedPlayer );
        Instance()->currentAction = Enums::Right;
    }

    if (InputManager::Instance()->KeyDown(Enums::Exit))
    {
        InputManager::Instance()->Update();
        return true;
    }

    if(InputManager::Instance()->KeyPress(Enums::Shoot))
    {
        my_struct *tear = new my_struct;
        tear->x = xPlayer;
        tear->y = yPlayer;
        tear->Action = currentAction;
        tears.push_back(*tear);
    }
    
    if (!tears.empty())
    {
        for (auto& tear : tears)
        {
            move_Tear(&tear);
            if (tear.x > width || tear.x < 0 || tear.y > height || tear.y < 0)
                tears.erase(tears.begin());
        }
    }

    tearAssets->draw( window,tears);
    
    return false;
}

void GameDatas::move_Tear(my_struct* tear)
{
    if ( tear->Action == Enums::Up )
    {
        tear->y -= ball_speed;
    }
    if ( tear->Action == Enums::Down )
    {
        tear->y += ball_speed;
    }
    if ( tear->Action == Enums::Left )
    {
        tear->x -= ball_speed;
    }
    if ( tear->Action == Enums::Right )
    {
        tear->x += ball_speed;
    }
}