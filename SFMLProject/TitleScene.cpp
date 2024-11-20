#include "stdafx.h"
#include "TitleScene.h"

#include "SpriteGameObject.h"
#include "MouseObject.h"
#include "UIButtonObject.h"
#include "StartButton.h"

void TitleScene::Init()
{
	Scene::Init();
}

void TitleScene::Enter()
{
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("title_screen", "graphics/title_screen.png", true);

	sf::Vector2f resolutionSize = sf::Vector2f(WindowManager::GetInstance().GetResolutionSize());

	SpriteGameObject* titleSprite = AddGameObject(new SpriteGameObject("title_screen", "TitleSprite"), LayerType::UI);
	titleSprite->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.25f });

	MouseObject* mouse = AddGameObject(new MouseObject(), LayerType::UI);

	StartButton* button = AddGameObject(new StartButton("DungGeunMo", "Button", 50), LayerType::UI);
	button->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.5f });

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);

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
