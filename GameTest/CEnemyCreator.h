#pragma once
#include <vector>
#include "CEnemy.h"

class CEnemyCreator
{
	float m_timeForNextEnemy = 0.0f;

	float m_respawnPoint = 1025.0f;

	float m_speedOfCreation = 1.0f;
public:
	std::vector<CEnemy*> enemies;

	CEnemy* CreateEnemy();

	void Update(float deltaTime);
	void KillAllEnemies();
	void GetPositionOfLastEnemy(float& x, float& y);

	void SetSpeed(float speed);

	void CheckAllCollisions();
};
