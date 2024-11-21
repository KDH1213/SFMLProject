#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"

GameManager::GameManager()
	: isRestart(false)
	, currentTimer(300.f)
	, currentScore(0)
	, life(3)
	, restartPath("temporaryStorage.json")
	, isPlayerDead(false)
{
	  
}
void GameManager::OnRestart()
{
	--life;
	isRestart = true;
}

void GameManager::OnSavePoint(const sf::Vector2f& restartPos)
{
	restartPosition = restartPos;
	SceneManager::GetInstance().GetCurrentScene()->Save(restartPath);
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
}
