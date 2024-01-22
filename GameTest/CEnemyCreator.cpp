#include "stdafx.h"
#include "CEnemyCreator.h"
#include "App/app.h"
#include "CCannonBall.h"
#include "CGameManager.h"

extern float GetRandomFloat(float a, float b);

extern std::vector<CGameObject*> gameObjects;
extern std::vector< CCannonBall* > cannonBalls;

CEnemy* CEnemyCreator::CreateEnemy()
{
    float speed = 0.05f;
    CSimpleSprite* enemySprite = App::CreateSprite(".\\Assets\\Enemies\\LightBandit.png", 8, 5);

    float randomXIncrement = GetRandomFloat(20.0f, 100.0f);

    enemySprite->SetPosition(m_respawnPoint + randomXIncrement, 90.0f);
    enemySprite->CreateAnimation(CEnemy::EnemyAnimation::ENEMY_RUNNING, speed, {8,9,10,11,12,13,14,15});
    enemySprite->CreateAnimation(CEnemy::EnemyAnimation::ENEMY_DEATH, speed * 4, { 32, 33, 34, 35,36 });
    enemySprite->CreateAnimation(CEnemy::EnemyAnimation::ENEMY_SLASH, speed * 4, { 16,17,18,19,20,21,22,23 });
    enemySprite->SetAnimation(0, false);
    enemySprite->SetScale(1.5f);
    CEnemy* enemy = new CEnemy();
    enemy->LinkSprite(enemySprite);
    gameObjects.push_back(enemy);
    enemies.push_back(enemy);
    return enemy;
}

void CEnemyCreator::Update(float deltaTime)
{
    std::vector<CEnemy*>::iterator enemyToDeleteIterator;
    for (enemyToDeleteIterator = enemies.begin(); enemyToDeleteIterator != enemies.end(); ++enemyToDeleteIterator)
    {
        (*enemyToDeleteIterator)->UpdateEnemy(deltaTime);
    }

    m_timeForNextEnemy -= deltaTime;

    if (m_timeForNextEnemy < 0.0f)
    {
        CreateEnemy();
        m_timeForNextEnemy = GetRandomFloat(1000.0f, 1010.0f + 4000.f * m_speedOfCreation);
        m_speedOfCreation -= 0.05;
    }

    CheckAllCollisions();
}

void CEnemyCreator::KillAllEnemies()
{
    for (unsigned int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->KillEnemy();
    }
}

void CEnemyCreator::GetPositionOfLastEnemy(float& x, float& y)
{
    enemies[enemies.size() - 1]->GetSprite()->GetPosition(x, y);
}

void CEnemyCreator::SetSpeed(float speed)
{
    m_speedOfCreation = speed;
}

void CEnemyCreator::CheckAllCollisions()
{
    for (int i = 0; i < cannonBalls.size(); i++)
    {
        float xPos, yPos;

        std::vector<CGameObject* > indexesToDelete;

        cannonBalls[i]->GetSprite()->GetPosition(xPos, yPos);

        if (cannonBalls[i]->GetIsColliding())
        {
            for (unsigned int j = 0; j < enemies.size(); j++)
            {
                bool collided = enemies[j]->CheckCollision(xPos, yPos);

                if (collided)
                {
                    enemies[j]->HitEnemy(1);
                }
            }
        }
    }

    bool hasErasedAll = false;

    while (!hasErasedAll)
    {
        CEnemy* enemyToDelete = nullptr;
        unsigned int indexForDelete = 0;
        std::vector<CEnemy*>::iterator enemyToDeleteIterator;
        for (enemyToDeleteIterator = enemies.begin(); enemyToDeleteIterator != enemies.end(); ++enemyToDeleteIterator)
        {
            if ((*enemyToDeleteIterator)->ShouldDeleteThis())
            {
                enemyToDelete = (*enemyToDeleteIterator);
                break;
            }
            ++indexForDelete;
        }

        if (enemyToDelete == nullptr)
        {
            break;
        }

        CGameManager::getGmInstance()->DeleteGameObjectByUniqueId(enemyToDelete->GetGameObjectID());
        enemies.erase(enemies.begin() + indexForDelete);
    }
}
