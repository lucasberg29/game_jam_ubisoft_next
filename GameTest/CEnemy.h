#pragma once
#include <cmath>

#include "CGameObject.h"

class CEnemy : public CGameObject
{
	bool m_isAlive = true;
	bool m_isSlashing = false;

	float m_initialPositionX, m_initialPositionY;
	float m_speedX, m_speedY;
	int m_health = 1;
	int m_enemyDamage = 1;

	bool m_deleteEnemy = false;

	float m_deathTimer = 600.0f;

	int m_enemyPoints = 10;

	float m_enemyTarget;

	float m_distanceToStop = 40.0f;

	const float INITIAL_TIME_TO_HIT = 1300.0f;
	float m_timeToHit = INITIAL_TIME_TO_HIT;
public:
	enum EnemyAnimation
	{
		ENEMY_RUNNING,
		ENEMY_DEATH,
		ENEMY_SLASH
	};

	CEnemy();

	void UpdateEnemy(float deltaTime);

	void HitEnemy(int damage);
	void KillEnemy();
	void ResetPosition();

	float GetSpeedX();
	void SetSpeed(float speed);

	bool CheckCollision(float x, float y);

	bool ShouldDeleteThis();


};

