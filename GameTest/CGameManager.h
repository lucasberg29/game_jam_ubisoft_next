#pragma once

#include <string>
#include <map>
#include <vector>
#include "CGameObject.h"

class CGameManager
{
    static CGameManager* gmInstance;

    CGameManager()
    {

    }

public:
    CGameManager(const CGameManager& obj) = delete;

    static CGameManager* getGmInstance()
    {
        if (gmInstance == nullptr)
        {
            gmInstance = new CGameManager();
            return gmInstance;
        }
        else
        {
            return gmInstance;
        }
    }

    // game objects
    CGameObject* FindCGameObjectByFriendlyName(std::string friendlyNameToFind);

    CSimpleSprite* FindSpriteByID(std::string friendlyNameToFind);

    static bool DeleteGameObjectByFriendlyName(std::string friendlyName);

    static bool DeleteGameObjectByUniqueId(unsigned int id);

    // ui

    // game manager
    void Update();
    void GameOver();

    void RestartGame();
    void Victory();
};