#include "stdafx.h"
#include "CCatapult.h"
#include "App/app.h"

extern std::vector< CGameObject* > gameObjects;
extern std::vector< CSimpleSprite*> sprites;

void CCatapult::UpdateCatapult(float deltaTime)
{
	if (m_isAnimating)
	{
		m_canInteract = false;
		m_animationTimer += deltaTime;
	}

	if (m_animationTimer > 300.0f)
	{
		m_canInteract = true;
		ClearChildren();
		this->StopAnimating();
		this->LoadCatapult();
		m_isAnimating = false;
		m_animationTimer = 0.0f;
		this->GetSprite()->SetFrame(2);
		//RemoveChildById(this->RemoveChildById())
	}
}

void CCatapult::SetIsAnimating(bool isAnimating)
{
	m_isAnimating = isAnimating;
}

void CCatapult::LoadCatapult()
{
	CSimpleSprite* cannonBall = App::CreateSprite(".\\Assets\\Projectile\\catapultBall.png", 1, 1);
	float cannonPositionX = 0;
	float cannonPositionY = 0;
	this->GetSprite()->GetPosition(cannonPositionX, cannonPositionY);
	cannonBall->SetPosition(cannonPositionX -35.0f, cannonPositionY  + 2.0f);
	cannonBall->SetScale(0.02f);

	CGameObject* cannonBallObject = new CGameObject();
	cannonBallObject->LinkSprite(cannonBall);
	cannonBallObject->friendlyName = "cannonball";
	gameObjects.push_back(cannonBallObject);
	sprites.push_back(cannonBall);

	m_cannonBall = cannonBallObject;
	AddChild(cannonBallObject);
}

CGameObject* CCatapult::GetCannonBall()
{
	return m_cannonBall;
}

void CCatapult::SetSpeed(float speed)
{
	m_speed = speed;
}

float CCatapult::GetSpeed()
{
	return m_speed;
}

void CCatapult::SetCanInteract(bool canInteract)
{
	m_canInteract = canInteract;
}

bool CCatapult::GetCanInteract()
{
	return m_canInteract;
}
