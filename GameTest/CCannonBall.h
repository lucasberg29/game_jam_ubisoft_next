#pragma once

#include "CGameObject.h"

class CCannonBall : public CGameObject
{
	CGameObject* m_cannonBall = nullptr;
	float m_animationTimer = 0.0f;
	bool m_isAnimating = false;
	bool m_canInteract = true;
	bool m_hasExploded = false;
	bool m_deleteThis = false;
	bool m_isColliding = false;

public:
	CCannonBall() {}
	void SetIsAnimating(bool isAnimating);
	void CCannonBall::UpdateCannonBall(float deltaTime);
	void LoadCatapult();
	CGameObject* GetCannonBall();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetCanInteract(bool canInteract);
	bool GetCanInteract();
	void Explode();

	bool ShouldDeleteThis();
	void SetDeleteThis(bool deleteThis);

	void SetIsColliding(bool isColliding);
	bool GetIsColliding();
};

