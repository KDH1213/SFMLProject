#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"
#include "UITextGameObject.h"

GameManager::GameManager()
	: isRestart(false)
	, currentTimer(400.f)
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
	, highscore(0)
	, isStartClearEvent(false)
	, currentEventTime(0.f)
	, clearEvnetScoreUpTime(0.02f)
	, waitTime(1.f)
	, isEndAdjustment(false)
	, isGameOver(false)
	, marioHP(1)
	, isPlaying(false)
{
	  
}


void GameManager::Update(float dt)
{
	if (!isGameClear)
	{
		currentTimer -= dt;
		timerUI->SetString(std::to_string((int)currentTimer));
	}

	if (isPlaying &&  !isPlayerDead && !isGameClear && currentTimer <= 0.f)
	{
		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->GetFSM().ChangeState(PlayerStateType::Dead);
		isPlayerDead = true;
	}

	if (isStartClearEvent)
	{
		currentEventTime += dt;
		if ((int)currentTimer == 0)
		{
			if (currentEventTime > waitTime)
			{
				countDown->stop();
				isEndAdjustment = true;
				isPlaying = false;
				// SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
				currentTimer = 0.f;
			}
		}
		else
			OnClearAdjustment();
	}
}


void GameManager::Reset()
{
	life = 3;
	isPlayerDead = false;
	currentCoinCount = 0;
	currentScore = 0;
	isStartClearEvent = false;
	isEndAdjustment = false;
	isGameOver = false;
	isPlaying = false;
}

void GameManager::OnClearAdjustment()
{
	if (currentEventTime > clearEvnetScoreUpTime)
	{
		currentTimer -= 1.f;
		currentEventTime = 0.f;
		AddScore(100);

		if (currentTimer < 100)
		{
			if (currentTimer < 10)
				timerUI->SetString("00" + std::to_string((int)currentTimer));
			else
				timerUI->SetString("0" + std::to_string((int)currentTimer));
		}
		else
			timerUI->SetString(std::to_string((int)currentTimer));
	}
}

void GameManager::OnRestart()
{
	--life;
	currentTimer = 400.f;
	isPlaying = true;
	isRestart = true;
}

void GameManager::OnSavePoint(const sf::Vector2f& restartPos)
{
	restartPosition = restartPos;
	SceneManager::GetInstance().GetCurrentScene()->Save(restartPath);
}

void GameManager::SetGameClear()
{
	isGameClear = true;
}

void GameManager::OnGameClearEvent()
{
	isStartClearEvent = true;
	currentTimer = (float)((int)currentTimer);
	countDown = SoundManger::GetInstance().PlaySfxGet(("CountDown"));
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

	if (currentTimer < 100)
	{
		if(currentTimer < 10)
			timerUI->SetString("00" + std::to_string((int)currentTimer));
		else
			timerUI->SetString("0" + std::to_string((int)currentTimer));
	}
	else
		timerUI->SetString(std::to_string((int)currentTimer));
	scoreUI->SetString(scoreString);
}

void GameManager::NextStage()
{
	isPlaying = false;
	InputManager::GetInstance().SetInputable(false);
	SceneIds currentId = SceneManager::GetInstance().GetCurrentSceneId();
	if (currentId == SceneIds::SceneDev1)
	{
		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		marioHP = player->GetCurrentHP();
		SceneManager::GetInstance().ChangeScene(SceneIds::Stage2);
		player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->ChangeMario(marioHP);

		isPlaying = true;
		currentTimer = 400.f;
	}
	else if (currentId == SceneIds::Stage2)
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
	}
	isEndAdjustment = false;
	isGameClear = false;
	isStartClearEvent = false;
}

void GameManager::ReStart()
{	
	if (life == 0)
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
		isGameOver = true;
	}
	else
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetCurrentSceneId());
		SceneManager::GetInstance().GetCurrentScene()->Load(restartPath);
		isRestart = false;

		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->SetPosition(restartPosition);
		player->ChangeSmallMario();
		SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->SetCameraPosition(restartPosition);
	}
}

void GameManager::PlayerDie()
{
	isPlayerDead = true;
	OnRestart();
}

void GameManager::HaveCoin()
{
	++currentCoinCount;
	currentScore += 200;

	if (currentCoinCount >= 100)
	{
		++life;
		currentCoinCount -= 100;

		SoundManger::GetInstance().PlaySfx("OneUp");
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

void GameManager::OnLifeUp()
{
	++life;
}

void GameManager::AddScore(int score)
{
	currentScore += score;

	std::string strScore = std::to_string(currentScore);
	int size = (int)strScore.size() - 1;
	for (int i = 5; i > 0; --i)
	{
		scoreString[i] = strScore[size--];
		if (size < 0)
			break;
	}

	scoreUI->SetString(scoreString);
}
