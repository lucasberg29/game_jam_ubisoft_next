#pragma once

#include "CGameManager.h"
#include "CCannonBall.h"

class CCatapult : public CGameObject
{
	CCannonBall* m_cannonBall = nullptr;
	float m_animationTimer = 0.0f;
	bool m_isAnimating = false;
	bool m_canInteract = true;
	float m_speed = 3.0f;
	int m_health = 3;
public:
	CCatapult() {}

	void UpdateCatapult(float deltaTime);

	void SetIsAnimating(bool isAnimating);

	void LoadCatapult();

	CCannonBall* GetCannonBall();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetCanInteract(bool canInteract);
	bool GetCanInteract();

	int GetHealth();
	
};