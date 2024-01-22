#include "stdafx.h"
#include "CCannonBall.h"
#include "App/app.h"

enum {
	EXPLOSION_IN_ORDER
};

void CCannonBall::Explode()
{
	if (!m_hasExploded)
	{
		m_hasExploded = true;
		m_isAnimating = true;
		this->UseGravity(false);
		StopVelocity();
		SetStatic(true);

		CSimpleSprite* explosion = App::CreateSprite(".\\Assets\\Projectile\\explosion.png", 8, 1);
		float posX, posY;
		this->GetSprite()->GetPosition(posX, posY);
		float speed = 1.0f / 15.0f;
		this->LinkSprite(explosion);
		explosion->SetPosition(posX, posY);
		explosion->CreateAnimation(EXPLOSION_IN_ORDER, speed, { 0,1,2,3,4,5,6,7 });
		explosion->SetAnimation(EXPLOSION_IN_ORDER);
	}
}

bool CCannonBall::ShouldDeleteThis()
{
	return this->m_deleteThis;
}

void CCannonBall::SetDeleteThis(bool deleteThis)
{
	m_deleteThis = deleteThis;
}

void CCannonBall::SetIsColliding(bool isColliding)
{
	this->m_isColliding = isColliding;
}

bool CCannonBall::GetIsColliding()
{
	return m_isColliding;
}

void CCannonBall::UpdateCannonBall(float deltaTime)
{
	if (m_isAnimating)
	{
		m_canInteract = false;
		m_animationTimer += deltaTime;
	}

	if (m_animationTimer > 300.0f)
	{
		m_deleteThis = true;
		//delete this;
		m_canInteract = true;
		ClearChildren();
		this->StopAnimating();
		this->LoadCatapult();
		m_isAnimating = false;
		m_animationTimer = 0.0f;
		this->GetSprite()->SetFrame(2);
	}
}


void CCannonBall::SetIsAnimating(bool isAnimating)
{
}

void CCannonBall::LoadCatapult()
{
}

CGameObject* CCannonBall::GetCannonBall()
{
	return nullptr;
}

void CCannonBall::SetSpeed(float speed)
{
}

float CCannonBall::GetSpeed()
{
	return 0.0f;
}

void CCannonBall::SetCanInteract(bool canInteract)
{
}

bool CCannonBall::GetCanInteract()
{
	return false;
}
