#include "stdafx.h"
#include "CGameManager.h"

extern std::vector< CGameObject* > gameObjects;


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

void CGameManager::Update()
{
}

void CGameManager::RestartGame()
{
	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		(*gameObjectsIterator)->ResetPosition();
	}
}
