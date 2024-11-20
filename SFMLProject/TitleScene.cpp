#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::Init()
{
	Scene::Init();
}

void TitleScene::Enter()
{

	Scene::Enter();
}

void TitleScene::Exit()
{
	Scene::Exit();
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);
}

void TitleScene::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void TitleScene::Save()
{
}

void TitleScene::Load()
{
}

void TitleScene::Save(const std::string& savePath)
{
}

void TitleScene::Load(const std::string& loadPath)
{
}

TitleScene::TitleScene()
	: Scene(SceneIds::SceneDev2)
{

}

TitleScene::~TitleScene()
{
}
