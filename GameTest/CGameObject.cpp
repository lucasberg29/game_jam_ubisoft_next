#include "stdafx.h"
#include "CGameObject.h"

unsigned int CGameObject::gameObjects_uniqueId = 1;

CGameObject::CGameObject()
{
	m_uniqueId = ++this->gameObjects_uniqueId;
}

void CGameObject::AddVelocity(float x, float y)
{
	m_velocity.x += x;
	m_velocity.y += y;
}

void CGameObject::Update(float deltaTime)
{
	if (m_static == true)
	{
		return;
	}

	if (m_isUsingGravity)
	{
		m_velocity.y -= m_gravity;
	}

	float x, y;
	m_objectSprite->GetPosition(x, y);
	x += m_velocity.x;
	y += m_velocity.y;
	m_objectSprite->SetPosition(x, y);


	//if (friendlyName == "catapult")
	//{
	//	if (m_isAnimating)
	//	{

	//	}
	//}
}

void CGameObject::LinkSprite(CSimpleSprite* objectSprite)
{
	float x, y;
	objectSprite->GetPosition(x, y);
	this->m_initialPosition.x = x;
	this->m_initialPosition.y = y;

	this->m_objectSprite = objectSprite;
}

void CGameObject::UseGravity(bool isUsinGravity)
{
	this->m_isUsingGravity = isUsinGravity;
}

void CGameObject::AddChild(CGameObject* child)
{
	this->m_children.push_back(child);
}

void CGameObject::RemoveChildById(unsigned int id)
{
	std::vector<CGameObject*>::iterator childrenIterator;
	for (childrenIterator = m_children.begin(); childrenIterator != m_children.end(); ++childrenIterator)
	{
		if ((*childrenIterator)->GetGameObjectID() == id)
		{
			m_children.erase(childrenIterator);
		}
	}
}

unsigned int CGameObject::GetGameObjectID()
{
	return m_uniqueId;
}

void CGameObject::ResetPosition()
{
	m_objectSprite->SetPosition(m_initialPosition.x, m_initialPosition.y);
	StopVelocity();
	m_isAnimating = false;
}

void CGameObject::StopAnimating()
{
	m_objectSprite->SetAnimation(-1);
	m_isAnimating = false;
}

void CGameObject::StopVelocity()
{
	m_velocity = Velocity(0.0f);
}

CSimpleSprite* CGameObject::GetSprite()
{
	return this->m_objectSprite;
}

void CGameObject::MoveObject(float x, float y)
{
	float initialX, initialY;
	m_objectSprite->GetPosition(initialX, initialY);
	initialX += x;
	initialY += y;
	m_objectSprite->SetPosition(initialX, initialY);

	std::vector<CGameObject*>::iterator childrenIterator;
	for (childrenIterator = m_children.begin(); childrenIterator != m_children.end(); ++childrenIterator)
	{
		(*childrenIterator)->MoveObject(x, y);
	}
}

void CGameObject::ClearChildren()
{
	m_children.clear();
}

void CGameObject::SetStatic(bool isStatic)
{
	m_static = isStatic;
}
