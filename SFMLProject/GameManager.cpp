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
	, scoreString("000000")
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
	if (currentCoinCount < 10)
		coinString = "0" + std::to_string(currentCoinCount);
	else
		coinString = std::to_string(currentCoinCount);

	std::string score = std::to_string(currentScore);
	int size = (int)score.size() - 1;
	for (int i = 5; i > 0 ; --i)
	{
		scoreString[i] = score[size--];
		if (size < 0)
			break;
	}

	coinUI->SetString(coinString);
	timerUI->SetString(std::to_string((int)currentTimer));
	scoreUI->SetString(scoreString);
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

	if (currentCoinCount >= 100)
	{
		++life;
		currentCoinCount -= 100;
	}

	if (currentCoinCount < 10)
		coinString = "0" + std::to_string(currentCoinCount);
	else
		coinString = std::to_string(currentCoinCount);

	std::string score = std::to_string(currentScore);
	int size = (int)score.size() - 1;
	for (int i = 5; i > 0; --i)
	{
		scoreString[i] = score[size--];
		if (size < 0)
			break;
	}

	coinUI->SetString(coinString);
	scoreUI->SetString(scoreString);

}
