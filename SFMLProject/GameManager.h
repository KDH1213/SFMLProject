#pragma once

class Player;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
	
	std::string		restartPath;

	float			currentTimer;
	unsigned int	currentScore;
	int				life;
	bool			isRestart;

public:

	bool IsRestart() { return isRestart; }
	void OnRestart();
	void OnSavePoint();

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

