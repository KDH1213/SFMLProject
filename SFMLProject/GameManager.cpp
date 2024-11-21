#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"
#include "UITextGameObject.h"

GameManager::GameManager()
	: isRestart(false)
	, currentTimer(300.f)
	, currentScore(0)
	, life(3)
	, restartPath("temporaryStorage.json")
	, isPlayerDead(false)
	, worldName("1-1")
	, currentCoinCount(0)
	, scoreUI(nullptr)
	, coinUI(nullptr)
	, timerUI(nullptr)
{
	  
}


void GameManager::Update(float dt)
{
	currentTimer -= dt;
	timerUI->SetString(std::to_string((int)currentTimer));

	if (!isPlayerDead && currentTimer <= 0.f)
	{
		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->GetFSM().ChangeState(PlayerStateType::Dead);
		isPlayerDead = true;
	}
}


void GameManager::OnRestart()
{
	--life;
	currentTimer = 400.f;
	isRestart = true;
}

void GameManager::OnSavePoint(const sf::Vector2f& restartPos)
{
	restartPosition = restartPos;
	SceneManager::GetInstance().GetCurrentScene()->Save(restartPath);
}

void GameManager::GameStartInit()
{
	coinUI->SetString(std::to_string(currentCoinCount));
	timerUI->SetString(std::to_string((int)currentTimer));
	scoreUI->SetString(std::to_string(currentScore));
}

void GameManager::ReStart()
{	
	SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetCurrentSceneId());
	SceneManager::GetInstance().GetCurrentScene()->Load(restartPath);
	isRestart = false;

	Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
	player->SetPosition(restartPosition);
	player->ChangeSmallMario();
	SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->SetCameraPosition(restartPosition);
}

void GameManager::PlayerDie()
{
	isPlayerDead = true;
	OnRestart();
}

void GameManager::HaveCoin()
{
	++currentCoinCount;
	currentScore += 1000;

	coinUI->SetString(std::to_string(currentCoinCount));
	scoreUI->SetString(std::to_string(currentScore));

	if (currentCoinCount >= 100)
	{
		++life;
		currentCoinCount -= 100;
	}
}
