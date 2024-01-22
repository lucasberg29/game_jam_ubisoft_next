#pragma once
#include "CGameObject.h"
#include <stack>

class CCrystal : public CGameObject
{
	float m_animationSpeed = 1.0f / 10.0f;
	int CRYSTAL_MAX_HEALTH = 10;
	int m_crystalHealth = CRYSTAL_MAX_HEALTH;

	const float HIT_ANIMATION_TIMER = 800.0f;
	float m_hitAnimationTimer = HIT_ANIMATION_TIMER;
	bool m_isSimulatingHit = false;

	std::stack<float> m_xPositionsWhenHit;
public:
	enum CrystalAnimation {
		IDLE,
		GETINNG_HIT
	};

	CCrystal();
	void HitCrystal(int damage);
	void SetAnimationSpeed(float animationSpeed);
	int GetCrystalHealth();

	void ResetHealth();
	void SimulateHit();

	void UpdateCrystal(float deltaTime);
};

