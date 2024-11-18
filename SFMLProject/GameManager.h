#pragma once

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
protected:
	GameManager() = default;
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

