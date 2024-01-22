#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include "App/app.h"


class UiManager
{
	struct LogMessage  {
		LogMessage(std::string message, float timer)
		{
			p_message = message;
			p_timer = timer;
		}
		std::string p_message;
		float p_timer;
	};

	float m_uiTimer = 0.0f;
	int m_playerScore = 0;
	int m_victoryScore = 100;

	float m_logTimer = 800.0f;

	bool m_hasFadedBackground = false;
	bool m_isGameOver = false;
	std::stack<LogMessage> m_logMessages;

	int m_backgroundObjectId = 0;
	//CSimpleSprite* fadedBackgroundSprite = nullptr;
public:
	void RenderUi();
	void UpdateUiTimer(float deltaTime);
	void AddToScore(int score);

	void Log(std::string messageToShow);
	void HandleLogMessages();

	bool GetIsGameOver();
	void SetIsGameOver(bool isGameOver);

	void RestartGame();
};