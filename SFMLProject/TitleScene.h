#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window)override;

	void Save() override;
	void Load() override;
	void Save(const std::string& savePath) override;
	void Load(const std::string& loadPath) override;
public:
	TitleScene();
	~TitleScene();
};