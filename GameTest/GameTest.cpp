//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "CGameObject.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CCatapult.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
//CSimpleSprite* testSprite;

std::vector< CGameObject* > gameObjects;
std::vector< CSimpleSprite*> sprites;
CSimpleSprite* catapultPlayer;
CSimpleSprite* cannonBall;

//CGameObject* catapult;
CCatapult* catapult;

CGameManager* CGameManager::gmInstance = NULL;
CSceneManager* sceneManager;

float mousePosx, mousePosy;

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
	sceneManager = new CSceneManager();
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

	CSimpleSprite* backgroundSky = App::CreateSprite(".\\Assets\\Background\\sky.png", 1, 1);
	backgroundSky->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgroundSky->SetScale(1.0f);
	sprites.push_back(backgroundSky);

	CSimpleSprite* backgrounMountains = App::CreateSprite(".\\Assets\\Background\\far-mountains.png", 1, 1);
	backgrounMountains->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgrounMountains->SetScale(1.0f);
	sprites.push_back(backgrounMountains);

	CSimpleSprite* backgrounTrees = App::CreateSprite(".\\Assets\\Background\\trees.png", 1, 1);
	backgrounTrees->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
	backgrounTrees->SetScale(1.0f);
	sprites.push_back(backgrounTrees);

	CSimpleSprite* ground1 = App::CreateSprite(".\\Assets\\ground.png", 1, 1);
	ground1->SetPosition(125.0f, 31.0f);
	ground1->SetScale(1.0f);
	sprites.push_back(ground1);

	CSimpleSprite* ground2 = App::CreateSprite(".\\Assets\\ground.png", 1, 1);
	ground2->SetPosition(380.0f, 31.0f);
	ground2->SetScale(1.0f);
	sprites.push_back(ground2);

	CSimpleSprite* ground3 = App::CreateSprite(".\\Assets\\ground.png", 1, 1);
	ground3->SetPosition(635.0f, 31.0f);
	ground3->SetScale(1.0f);
	sprites.push_back(ground3);

	CSimpleSprite* ground4 = App::CreateSprite(".\\Assets\\ground.png", 1, 1);
	ground4->SetPosition(890.0f, 31.0f);
	ground4->SetScale(1.0f);
	sprites.push_back(ground4);

	CSimpleSprite* ground5 = App::CreateSprite(".\\Assets\\ground.png", 1, 1);
	ground5->SetPosition(1090.0f, 31.0f);
	ground5->SetScale(1.0f);
	sprites.push_back(ground5);

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

	//cannonBall = App::CreateSprite(".\\Assets\\Projectile\\catapultBall.png",1,1);
	//float cannonPositionX = 0;
	//float cannonPositionY = 0;
	//catapultPlayer->GetPosition(cannonPositionX, cannonPositionY);
	//cannonBall->SetPosition(66.0f,102.0f);
	//cannonBall->SetScale(0.02f);

	//CGameObject* cannonBallObject = new CGameObject();
	//cannonBallObject->LinkSprite(cannonBall);
	//cannonBallObject->friendlyName = "cannonball";
	//gameObjects.push_back(cannonBallObject);
	//sprites.push_back(cannonBall);
	//catapult->AddChild(cannonBallObject);

	catapult->LoadCatapult();
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

	std::vector<CSimpleSprite*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); ++it) 
	{
		(*it)->Update(deltaTime);
	}

	std::vector<CGameObject*>::iterator gameObjectsIterator;
	for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++gameObjectsIterator)
	{
		(*gameObjectsIterator)->Update(deltaTime);
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
		if (catapult->GetCanInteract())
		{
			App::PlaySound(".\\TestData\\Test.wav");

			catapultPlayer->SetAnimation(ANIM_RELEASE, false);
			catapult->SetIsAnimating(true);

			CGameObject* cannonBall = catapult->GetCannonBall();
			cannonBall->StopVelocity();
			cannonBall->AddVelocity(5.0f, 5.0f);
			cannonBall->UseGravity(true);
		}
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		CGameManager::getGmInstance()->RestartGame();
		CGameManager::getGmInstance()->FindCGameObjectByFriendlyName("catapult")->StopAnimating();
		//catapult->GetCannonBall()


		CGameManager::getGmInstance()->FindCGameObjectByFriendlyName("cannonball")->UseGravity(false);
		catapultPlayer->SetFrame(2);
	}
	

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
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{

		std::string mousePosition = "x: " + std::to_string(mousePosx) + " y: " + std::to_string(mousePosy);

		App::Print(100.0f, 500.0f, mousePosition.c_str());

		App::PlaySound(".\\TestData\\Test.wav");


	}

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	std::vector<CSimpleSprite*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); ++it)
	{
		(*it)->Draw();
	}

	//std::vector<CGameObject*>::iterator gameObjectsIterator;
	//for (gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ++it)
	//{
	//	(*gameObjectsIterator)->Draw();
	//}

	//cannonBall->Draw();

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Draw();

	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	std::string mousePosition = "x: " + std::to_string(mousePosx) + " y: " + std::to_string(mousePosy);
	App::Print(15, 745, mousePosition.c_str());



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