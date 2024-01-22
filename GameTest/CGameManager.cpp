#include "stdafx.h"
#include "CGameManager.h"
#include "UiManager.h"
#include "CCrystal.h"
#include "CCannonBall.h"
#include "CCatapult.h"

extern std::vector< CCannonBall* > cannonBalls;
extern std::vector< CGameObject* > gameObjects;
extern std::vector< CSimpleSprite* > sprites;
extern UiManager* uiManager;
extern CCrystal* gameCrystal;
extern CCatapult* catapult;

CGameObject* CGameManager::FindCGameObjectByFriendlyName(std::string friendlyNameToFind)
{
	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		if ((*gameObjectsIterator)->friendlyName == friendlyNameToFind)
		{
			return (*gameObjectsIterator);
		}
	}

    return nullptr;
}

bool CGameManager::DeleteGameObjectByFriendlyName(std::string friendlyName)
{
    return false;
}

bool CGameManager::DeleteGameObjectByUniqueId(unsigned int id)
{
	std::vector<CGameObject*>::iterator gameObjectsIterator;
	CGameObject* objectToDelete = nullptr;
	unsigned int indexToDelete = 0;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		if ((*gameObjectsIterator)->GetGameObjectID() == id)
		{
			objectToDelete = (*gameObjectsIterator);
			break;
		}

		++indexToDelete;
	}

	if (objectToDelete == nullptr)
	{
		return false;
	}

	delete objectToDelete;
	gameObjects.erase(gameObjects.begin() + indexToDelete);
	return true;
}

void CGameManager::Update()
{
}

void CGameManager::GameOver()
{
	uiManager->Log("Game Over!");
}

void CGameManager::RestartGame()
{
	gameCrystal->ResetHealth();

	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		(*gameObjectsIterator)->ResetPosition();
	}
	
	std::vector<CCannonBall*>::iterator cannonBallsIterator;
	for (cannonBallsIterator = cannonBalls.begin(); cannonBallsIterator != cannonBalls.end(); ++cannonBallsIterator)
	{
		(*cannonBallsIterator)->SetDeleteThis(true);
	}

	uiManager->RestartGame();
}

void CGameManager::Victory()
{
	uiManager->Log("Victory!");
}
