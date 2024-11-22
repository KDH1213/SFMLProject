#pragma once

class Player;
class UITextGameObject;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
	UITextGameObject* coinUI;
	UITextGameObject* timerUI;
	UITextGameObject* scoreUI;


	std::string		restartPath;
	std::string		worldName;
	sf::Vector2f	restartPosition;

	float			currentTimer;
	unsigned int	currentCoinCount;
	unsigned int	currentScore;
	int				life;
	bool			isRestart;
	bool			isPlayerDead;

	int				highscore;

public:

	bool IsRestart() { return isRestart; }
	void OnRestart();
	void OnSavePoint(const sf::Vector2f& restartPos);
	void SetHighScore(int score) { highscore = score; }

	void GameStartInit();

	void ReStart();
	void PlayerDie();
	void HaveCoin();

	const std::string& GetWorldName() { return worldName; }

	void SetTimerUI(UITextGameObject* ui) { timerUI = ui; }
	void SetCoinUI(UITextGameObject* ui) { coinUI = ui; }
	void SetScoreUI(UITextGameObject* ui) { scoreUI = ui; }

public:
	void Update(float dt);

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

