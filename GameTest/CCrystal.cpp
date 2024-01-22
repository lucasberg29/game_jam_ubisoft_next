#include "stdafx.h"
#include "CCrystal.h"
#include "App/app.h"

#include "CGameManager.h"
#include "UiManager.h"

extern UiManager* uiManager;

CCrystal::CCrystal()
{
	CSimpleSprite* crystalSprite = App::CreateSprite(".\\Assets\\Crystal\\Crystal.png", 24, 1);
	crystalSprite->CreateAnimation(IDLE, m_animationSpeed, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 });
	crystalSprite->SetPosition(300.0f,100.0f);
	//crystalSprite->SetPosition(800.0f, 100.0f);

	crystalSprite->SetScale(1.0f);
	crystalSprite->SetAnimation(IDLE, true);
	LinkSprite(crystalSprite);
}

void CCrystal::HitCrystal(int damage)
{
	if (uiManager->GetIsGameOver())
	{

	}
	else
	{
		if (m_crystalHealth - damage <= 0)
		{
			m_crystalHealth = 0;
			CGameManager::getGmInstance()->GameOver();
		}

		m_crystalHealth -= damage;
		SimulateHit();
	}

}

void CCrystal::SetAnimationSpeed(float animationSpeed)
{
	m_animationSpeed = animationSpeed;
}

int CCrystal::GetCrystalHealth()
{
	return m_crystalHealth;
}

void CCrystal::ResetHealth()
{
	this->m_crystalHealth = CRYSTAL_MAX_HEALTH;
}

void CCrystal::SimulateHit()
{
	if (!m_isSimulatingHit)
	{
		m_isSimulatingHit = true;

		float xPos, yPos;
		GetSprite()->GetPosition(xPos, yPos);

		m_xPositionsWhenHit.push(xPos);
		m_xPositionsWhenHit.push(xPos - 4.0f);
		m_xPositionsWhenHit.push(xPos);
		m_xPositionsWhenHit.push(xPos + 4.0f);
		m_xPositionsWhenHit.push(xPos);
		m_xPositionsWhenHit.push(xPos - 4.0f);
		m_xPositionsWhenHit.push(xPos);
	}
}

void CCrystal::UpdateCrystal(float deltaTime)
{
	if (m_isSimulatingHit)
	{
		m_hitAnimationTimer -= deltaTime / 1000.f;

		if (!m_xPositionsWhenHit.empty())
		{
			float yPos = 100.0f;
			float xPos = m_xPositionsWhenHit.top();
			GetSprite()->SetPosition(xPos, yPos);
			m_xPositionsWhenHit.pop();
		}
		else
		{
			m_isSimulatingHit = false;
		}
	}
}
