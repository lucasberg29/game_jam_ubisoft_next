
#include "stdafx.h"
#include "UiManager.h"
#include "CCatapult.h"
#include "CCrystal.h"
#include "CEnemyCreator.h"

extern CEnemyCreator* enemyCreator;;
extern CCatapult* catapult;
extern CCrystal* gameCrystal;
extern std::vector<CGameObject* > gameObjects;

void UiManager::RenderUi()
{
	// mouse info
	HandleLogMessages();

	if (!m_isGameOver)
	{
		std::string scoreText = "SCORE: " + std::to_string(m_playerScore) + " / " + std::to_string(m_victoryScore);
		App::Print(15, 745, scoreText.c_str());

		std::string crystalHealth = "HEALTH: " + std::to_string(gameCrystal->GetCrystalHealth());
		App::Print(15, 645, crystalHealth.c_str());
		//App::Print(605, 245, catapultHealth.c_str());


		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << m_uiTimer;

		std::string stringValue = oss.str();
		std::string timeText = "TIMER: " + stringValue;
		App::Print(250, 745, timeText.c_str());
	}
}

void UiManager::UpdateUiTimer(float deltaTime)
{
	m_uiTimer += (deltaTime / 1000.0f);
}

void UiManager::AddToScore(int score)
{
	if (m_playerScore + score >= m_victoryScore)
	{
		m_playerScore = m_victoryScore;
		CGameManager::getGmInstance()->Victory();
	}

	m_playerScore += score;
}

void UiManager::Log(std::string messageToShow)
{
	m_logMessages.push(LogMessage(messageToShow, m_logTimer));
}

void UiManager::HandleLogMessages()
{
	if (!m_logMessages.empty())
	{
		LogMessage currentMessage = m_logMessages.top();

		if (currentMessage.p_timer >= 0.0f)
		{
			if (currentMessage.p_message == "Game Over!")
			{
				m_isGameOver = true;
			}

			if (currentMessage.p_message == "Victory!")
			{
				m_isGameOver = true;
			}

			if (!m_hasFadedBackground)
			{
				m_hasFadedBackground = true;
				CSimpleSprite* fadedBackgroundSprite = App::CreateSprite(".\\Assets\\Background\\background_real_fade.png", 1, 1);
				fadedBackgroundSprite->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
				CGameObject* fadedBackground = new CGameObject();
				fadedBackground->LinkSprite(fadedBackgroundSprite);
				m_backgroundObjectId = fadedBackground->GetGameObjectID();
				gameObjects.push_back(fadedBackground);
			}

			currentMessage.p_timer -= 1.0f;

			App::Print(APP_VIRTUAL_WIDTH / 2.0f - (currentMessage.p_message.length() * 4), APP_VIRTUAL_HEIGHT / 2.0f, currentMessage.p_message.c_str());
		}
	}
}

bool UiManager::GetIsGameOver()
{
	return m_isGameOver;
}

void UiManager::SetIsGameOver(bool isGameOver)
{
	m_isGameOver = isGameOver;
}

void UiManager::RestartGame()
{
	//m_isGameOver = false;
	m_hasFadedBackground = false;
	m_uiTimer = 0.0f;
	SetIsGameOver(false);

	while (!m_logMessages.empty())
	{
		m_logMessages.pop();
	}

	enemyCreator->KillAllEnemies();
	m_playerScore = 0;
	CGameManager::getGmInstance()->DeleteGameObjectByUniqueId(m_backgroundObjectId);
	catapult->ClearChildren();
	catapult->LoadCatapult();
}
