#pragma once
#include "Assets/TearAssets.h"
#include "Managers/TextureMgr.h"

class GameDatas
{
    public:

        GameDatas();
        static GameDatas *pInstance;
        static GameDatas* Instance();
        int update(sf::RenderWindow &window);
    
        void move_Tear(my_struct* tear);

        float xPlayer;
        float yPlayer;
        float height;
        float width;
        float SpeedPlayer;
        float ball_speed;

        std::vector<my_struct> tears;
    
        Enums::actions currentAction;

        TearAssets *tearAssets;
    
};
