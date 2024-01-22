//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <time.h>
#include <iomanip>
#include <sstream>
//------------------------------------------------------------------------
#include "app\app.h"
#include "CGameObject.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CCatapult.h"
#include "CCannonBall.h"
#include "CEnemy.h"
#include "CEnemyCreator.h"

#include "CCrystal.h"
#include "UiManager.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
//CSimpleSprite* testSprite;

CEnemyCreator* enemyCreator;

std::vector< CCannonBall* > cannonBalls;
std::vector< CGameObject* > gameObjects;
std::vector< CGameObject* > gameObjectsToDelete;

std::vector< CSimpleSprite*> sprites;
CSimpleSprite* catapultPlayer;
CSimpleSprite* cannonBall;

std::vector<int> indexesToDelete;

//CGameObject* catapult;
CCatapult* catapult;

CGameManager* CGameManager::gmInstance = NULL;
CSceneManager* sceneManager;

UiManager* uiManager;

CCrystal* gameCrystal;

float mousePosx, mousePosy;

float GetRandomFloat(float a, float b);

void PlaySoundFromFile(std::string fileName);

//unsigned int* playerScore = 0;
float timer = 0.0f;

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
	ANIM_RELEASE
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{

	srand((unsigned int)time(0));

	sceneManager = new CSceneManager();
	uiManager = new UiManager();
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	//testSprite->SetPosition(400.0f, 400.0f);
	//float speed = 1.0f / 15.0f;
	//testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	//testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	//testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	//testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	//testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------

	// background
	float speed = 1.0f / 15.0f;

	CSimpleSprite* backgroundSkySprite = App::CreateSprite(".\\Assets\\Background\\sky.png", 1, 1);
	backgroundSkySprite->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgroundSkySprite->SetScale(1.0f);
	CGameObject* backgroundSky = new CGameObject();
	backgroundSky->LinkSprite(backgroundSkySprite);
	gameObjects.push_back(backgroundSky);

	CSimpleSprite* backgrounMountainsSprite = App::CreateSprite(".\\Assets\\Background\\far-mountains.png", 1, 1);
	backgrounMountainsSprite->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgrounMountainsSprite->SetScale(1.0f);
	CGameObject* backgrounMountains = new CGameObject();
	backgrounMountains->LinkSprite(backgrounMountainsSprite);
	gameObjects.push_back(backgrounMountains);

	CSimpleSprite* backgrounTreesSprite = App::CreateSprite(".\\Assets\\Background\\trees.png", 1, 1);
	backgrounTreesSprite->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgrounTreesSprite->SetScale(1.0f);
	CGameObject* backgrounTrees = new CGameObject();
	backgrounTrees->LinkSprite(backgrounTreesSprite);
	gameObjects.push_back(backgrounTrees);

	unsigned int numOfGroundUnits = 5;
	for (unsigned int i = 0; i < numOfGroundUnits; i++)
	{
		CSimpleSprite* groundSprite = App::CreateSprite(".\\Assets\\ground.png", 1, 1);

		
		groundSprite->SetPosition(125.0f + (255 * i), 31.0f);
		groundSprite->SetScale(1.0f);

		CGameObject* ground = new CGameObject();
		ground->LinkSprite(groundSprite);
		gameObjects.push_back(ground);
	}

	// catapult player
	catapultPlayer = App::CreateSprite(".\\Assets\\Catapult\\catapult.png", 3, 4);
	catapultPlayer->SetPosition(100.0f, 85.0f);
	catapultPlayer->SetFrame(2);
	catapultPlayer->SetScale(0.4f);
	catapultPlayer->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	catapultPlayer->CreateAnimation(ANIM_RELEASE, speed, { 2, 1, 0, 1, 2 });
	catapult = new CCatapult();
	catapult->friendlyName = "catapult";
	catapult->LinkSprite(catapultPlayer);
	gameObjects.push_back(catapult);
	sprites.push_back(catapultPlayer);

	catapult->LoadCatapult();

	CSimpleSprite* explosionSprite = App::CreateSprite(".\\Assets\\Projectile\\explosion.png", 8, 1);
	explosionSprite->SetPosition(100.f, 110.0f);
	explosionSprite->CreateAnimation(ANIM_FORWARDS, 10.0f, { 0,1,2,3,4,5,6,7 });
	explosionSprite->SetAnimation(ANIM_FORWARDS, false);
	sprites.push_back(explosionSprite);
	CGameObject* explosion = new CGameObject();
	explosion->LinkSprite(explosionSprite);
	//gameObjects.push_back(explosion);

	// enemies

	//unsigned int numberOfEnemies = 10;

	//float lastEnemyXPos = 1025.0f;
	//for (unsigned int i = 0; i < numberOfEnemies; i++)
	//{
	//	CSimpleSprite* enemySprite = App::CreateSprite(".\\Assets\\Enemies\\LightBandit.png", 8, 5);

	//	float randomXIncrement = GetRandomFloat(20.0f, 100.0f);

	//	enemySprite->SetPosition(lastEnemyXPos + randomXIncrement, 90.0f);
	//	enemySprite->CreateAnimation(ANIM_FORWARDS, speed, { 8,9,10,11,12,13,14,15 });
	//	enemySprite->SetAnimation(ANIM_FORWARDS, false);
	//	enemySprite->SetScale(1.5f);
	//	CEnemy* enemy = new CEnemy();
	//	enemy->LinkSprite(enemySprite);
	//	gameObjects.push_back(enemy);
	//	lastEnemyXPos += + randomXIncrement;
	//}


	enemyCreator = new CEnemyCreator();


	// Crystal
	gameCrystal = new CCrystal();

	gameObjects.push_back(gameCrystal);

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Update(deltaTime);
	App::GetMousePos(mousePosx, mousePosy);

	catapult->UpdateCatapult(deltaTime);

	uiManager->UpdateUiTimer(deltaTime);

	gameCrystal->UpdateCrystal(deltaTime);

	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		(*gameObjectsIterator)->Update(deltaTime);
		(*gameObjectsIterator)->GetSprite()->Update(deltaTime);
	}

	
	std::vector<CCannonBall*>::iterator cannonBallsIterator;
	for (cannonBallsIterator = cannonBalls.begin(); cannonBallsIterator != cannonBalls.end(); ++cannonBallsIterator)
	{
		(*cannonBallsIterator)->UpdateCannonBall(deltaTime);
		float x, y;
		(*cannonBallsIterator)->GetSprite()->GetPosition(x, y);

		if (y < 65.0f)
		{
			(*cannonBallsIterator)->Explode();
		}
	}

	bool hasErasedAll = false;

	while (!hasErasedAll)
	{
		CCannonBall* ballToDelete = nullptr;
		unsigned int indexForDelete = 0;

		for (cannonBallsIterator = cannonBalls.begin(); cannonBallsIterator != cannonBalls.end(); ++cannonBallsIterator)
		{
			if ((*cannonBallsIterator)->ShouldDeleteThis())
			{
				ballToDelete = (*cannonBallsIterator);
				break;
			}
			++indexForDelete;
		}

		if (ballToDelete == nullptr)
		{
			break;
		}

		CGameManager::getGmInstance()->DeleteGameObjectByUniqueId(ballToDelete->GetGameObjectID());
		//delete ballToDelete;
		cannonBalls.erase(cannonBalls.begin() + indexForDelete);
	}

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float catapulSpeed = catapult->GetSpeed();
		catapult->MoveObject(1.0f * catapulSpeed, 0.0f);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float catapulSpeed = catapult->GetSpeed();
		catapult->MoveObject(-1.0f * catapulSpeed, 0.0f);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		if (uiManager->GetIsGameOver())
		{
			CGameManager::getGmInstance()->RestartGame();
		}
		else
		{
			if (catapult->GetCanInteract())
			{
				App::PlaySound(".\\TestData\\Test.wav");

				//warrior_death
				//App::PlaySound(".\\Assets\\Audio\\warrior_death.wav");

				catapultPlayer->SetAnimation(ANIM_RELEASE, false);
				catapult->SetIsAnimating(true);

				CCannonBall* cannonBall = catapult->GetCannonBall();
				cannonBall->StopVelocity();
				cannonBall->AddVelocity(5.0f, 5.0f);
				cannonBall->UseGravity(true);
				cannonBall->SetIsColliding(true);
			}
		}
	}

	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	//{
	//	CGameManager::getGmInstance()->RestartGame();
	//	CGameManager::getGmInstance()->FindCGameObjectByFriendlyName("catapult")->StopAnimating();
	//	//catapult->GetCannonBall()

	//	CGameManager::getGmInstance()->FindCGameObjectByFriendlyName("cannonball")->UseGravity(false);
	//	catapultPlayer->SetFrame(2);
	//}

	enemyCreator->Update(deltaTime);
	
	timer += (deltaTime / 1000.f);

	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	//{
	//	testSprite->SetScale(testSprite->GetScale() + 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	//{
	//	testSprite->SetScale(testSprite->GetScale() - 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	//{
	//	testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	//{
	//	testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	//{
	//	testSprite->SetAnimation(-1);
	//}
	////------------------------------------------------------------------------
	//// Sample Sound.
	////------------------------------------------------------------------------
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	//{
	//	App::PlaySound(".\\TestData\\Test.wav");
	//	testSprite->SetAnimation(-1);

	//}



	////////////////////////
	//if (App::GetController().GetLeftThumbStickX() > 0.5f)
	//{
	//	testSprite->SetAnimation(ANIM_RIGHT);
	//	float x, y;
	//	testSprite->GetPosition(x, y);
	//	x += 1.0f;
	//	testSprite->SetPosition(x, y);
	//}
	//if (App::GetController().GetLeftThumbStickX() < -0.5f)
	//{
	//	testSprite->SetAnimation(ANIM_LEFT);
	//	float x, y;
	//	testSprite->GetPosition(x, y);
	//	x -= 1.0f;
	//	testSprite->SetPosition(x, y);
	//}
 //   if (App::GetController().GetLeftThumbStickY() > 0.5f)
 //   {
 //       testSprite->SetAnimation(ANIM_FORWARDS);
 //       float x, y;
 //       testSprite->GetPosition(x, y);
 //       y += 1.0f;
 //       testSprite->SetPosition(x, y);
 //   }
	//if (App::GetController().GetLeftThumbStickY() < -0.5f)
	//{
	//	testSprite->SetAnimation(ANIM_BACKWARDS);
	//	float x, y;
	//	testSprite->GetPosition(x, y);
	//	y -= 1.0f;
	//	testSprite->SetPosition(x, y);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	//{
	//	testSprite->SetScale(testSprite->GetScale() + 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	//{
	//	testSprite->SetScale(testSprite->GetScale() - 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	//{
	//	testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	//{
	//	testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	//{
	//	testSprite->SetAnimation(-1);
	//}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	//{
	//	std::string mousePosition = "x: " + std::to_string(mousePosx) + " y: " + std::to_string(mousePosy);
	//	App::Print(100.0f, 500.0f, mousePosition.c_str());
	//	App::PlaySound(".\\TestData\\Test.wav");
	//}


}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//std::vector<CSimpleSprite*>::iterator it;
	//for (it = sprites.begin(); it != sprites.end(); ++it)
	//{
	//	(*it)->Draw();
	//}

	//std::vector<CSimpleSprite*>::iterator it;
	//for (it = sprites.begin(); it != sprites.end(); ++it)
	//{
	//	(*it)->Draw();
	//}

	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		(*gameObjectsIterator)->GetSprite()->Draw();
	}

	//cannonBall->Draw();

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Draw();

	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	//std::string mousePosition = "x: " + std::to_string(mousePosx) + " y: " + std::to_string(mousePosy);
	//App::Print(15, 745, mousePosition.c_str());

	uiManager->RenderUi();

	//std::string scoreText = "SCORE: " + std::to_string(playerScore); 
	//App::Print(15, 745, scoreText.c_str());

	//std::string catapultHealth = "HEALTH: " + std::to_string(catapult->GetHealth());
	//App::Print(15, 645, catapultHealth.c_str());

	//std::ostringstream oss;
	//oss << std::fixed << std::setprecision(2) << timer;

	//std::string stringValue = oss.str();
	//std::string timeText = "TIMER: " + stringValue;
	//App::Print(250, 745, timeText.c_str());

	//App::Print(100, 100, "Sample Text");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	//static float a = 0.0f;
	//float r = 1.0f;
	//float g = 1.0f;
	//float b = 1.0f;
	//a += 0.1f;
	//for (int i = 0; i < 20; i++)
	//{

	//	float sx = 200 + sinf(a + i * 0.1f)*60.0f;
	//	float sy = 200 + cosf(a + i * 0.1f)*60.0f;
	//	float ex = 700 - sinf(a + i * 0.1f)*60.0f;
	//	float ey = 700 - cosf(a + i * 0.1f)*60.0f;
	//	g = (float)i / 20.0f;
	//	b = (float)i / 20.0f;
	//	App::DrawLine(sx, sy, ex, ey,r,g,b);
	//}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//delete testSprite;
	//------------------------------------------------------------------------
}


float GetRandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


void PlaySoundFromFile(std::string fileName)
{
	App::PlaySound(fileName.c_str());
}