#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
	: isRestart(false)
	, currentTimer(300.f)
	, currentScore(0)
	, life(3)
	, restartPath("temporaryStorage.json")
{
	  
}
void GameManager::OnRestart()
{
	--life;
	SceneManager::GetInstance().GetCurrentScene()->Load(restartPath);
}

void GameManager::OnSavePoint()
{
	SceneManager::GetInstance().GetCurrentScene()->Save(restartPath);
}
