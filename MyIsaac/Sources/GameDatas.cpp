#include "Headers/GameDatas.h"

GameDatas *GameDatas::pInstance = nullptr;

GameDatas* GameDatas::Instance()
{
    if (pInstance == nullptr)
        pInstance = new GameDatas;

    return pInstance;
}
