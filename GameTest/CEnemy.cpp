#include "stdafx.h"
#include "CEnemy.h"
#include "CGameManager.h"
#include "UiManager.h"
#include "CCrystal.h"

//extern void AddToScore(int score);

extern UiManager* uiManager;
extern CCrystal* gameCrystal;

extern void PlaySoundFromFile(std::string fileName);

CEnemy::CEnemy():
	m_speedX(- 1.3f)
{
	float enemyTargetX, enemyTargetY;
	gameCrystal->GetSprite()->GetPosition(enemyTargetX, enemyTargetY);
	m_enemyTarget = enemyTargetX;
	AddVelocity(m_speedX, 0.0f);
}

void CEnemy::HitEnemy(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
	{
		m_isAlive = false;
		GetSprite()->SetAnimation(1, false);
	}
}

void CEnemy::KillEnemy()
{
	//PlaySoundFromFile(".\\Assets\\Audio\\warrior_death.wav");
	//App::PlaySound(".\\Assets\\Audio\\warrior_death.wav");

	m_deleteEnemy = true;
	uiManager->AddToScore(m_enemyPoints);
}

void CEnemy::UpdateEnemy(float deltaTime)
{
	if (m_isAlive)
	{
		if (m_isSlashing)
		{
			m_timeToHit -= deltaTime;

			if (m_timeToHit <= 0.0f)
			{
				gameCrystal->HitCrystal(m_enemyDamage);
				m_timeToHit = INITIAL_TIME_TO_HIT + 1.0f;
			}
		}
		else
		{
			float currentX, currentY;
			this->GetSprite()->GetPosition(currentX, currentY);

			if (currentX - m_enemyTarget < m_distanceToStop)
			{
				StopVelocity();
				GetSprite()->SetAnimation(ENEMY_SLASH);
				m_isSlashing = true;
			}
		}
	}
	else
	{
		m_deathTimer -= deltaTime;

		if (m_deathTimer <= 0.0f)
		{
			KillEnemy();
		}
	}
}

void CEnemy::ResetPosition()
{

}

float CEnemy::GetSpeedX()
{
	return m_speedX;
}

void CEnemy::SetSpeed(float speed)
{

}

bool CEnemy::CheckCollision(float x, float y)
{
	float collisionDistance = 40.0f;

	float xPos, yPos;
	GetSprite()->GetPosition(xPos, yPos);

	float distance = std::sqrt((x - xPos) * (x - xPos) + (y - yPos) * (y - yPos));

	if (distance <= collisionDistance) 
	{
		return true;
	}
	else 
	{
		return false;
	}

}

bool CEnemy::ShouldDeleteThis()
{
	return m_deleteEnemy;
}
