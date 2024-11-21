#pragma once

class Player;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
	
	std::string		restartPath;
	sf::Vector2f	restartPosition;

	float			currentTimer;
	unsigned int	currentCoinCount;
	unsigned int	currentScore;
	int				life;
	bool			isRestart;
	bool			isPlayerDead;

public:

	bool IsRestart() { return isRestart; }
	void OnRestart();
	void OnSavePoint(const sf::Vector2f& restartPos);

	void ReStart();
	void PlayerDie();
	void HaveCoin();

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

