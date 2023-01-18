#pragma once

class GameDatas
{
    public:

        enum actions
        {
            Up,
            Down,
            Left,
            Right,
            Shoot,
            Exit,
        };


        static GameDatas *pInstance;
        static GameDatas* Instance();

        float xPlayer;
        float yPlayer;
        actions currentAction;
    
};
