#pragma once
#include "App/SimpleSprite.h"

class CGameObject
{
public:
	struct Velocity {
		float x, y;

		Velocity() {}

		Velocity(float velocity) :
			x(velocity),
			y(velocity)
		{};
	};

	struct Position {
		float x, y;
	};

	CGameObject();

	void AddVelocity(float x, float y);

	void Update(float deltaTime);

	void LinkSprite(CSimpleSprite* objectSprite);

	void UseGravity(bool isUsinGravity);

	std::string friendlyName;

	void AddChild(CGameObject* child);

	void RemoveChildById(unsigned int id);

	unsigned int GetGameObjectID();

	void ResetPosition();

	void StopAnimating();
	void StopVelocity();

	CSimpleSprite* GetSprite();

	void MoveObject(float x, float y);

	void ClearChildren();
	void SetStatic(bool isStatic);

private:
	Position m_initialPosition;
	Velocity m_velocity;
	bool m_isUsingGravity = false;
	float m_gravity = 0.1f;
	CSimpleSprite* m_objectSprite;
	std::vector<CGameObject*> m_children;
	unsigned int m_uniqueId;
	static unsigned int gameObjects_uniqueId;

	bool m_isAnimating = false;
	float m_animationTimer = 0.0f;

	bool m_isColiding = false;
	bool m_static = false;
};

