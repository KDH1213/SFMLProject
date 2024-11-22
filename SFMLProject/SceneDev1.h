#pragma once
#include "Scene.h"
class Player;

class SceneDev1 : public Scene
{
private:
	Player*		player;
	Rectangle	cameraLimitRect;
	Rectangle	currentCameraLimitRect;

public:
	void CollisitionCheck();
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window)override;

	void Save(const std::string& savePath) override;
	void Load(const std::string& loadPath) override;
public:
	SceneDev1();
	~SceneDev1();

};

