#include "stdafx.h"
#include "TitleScene.h"

#include "RectSpriteGameObject.h"
#include "MouseObject.h"
#include "UIButtonObject.h"
#include "StartButton.h"
#include "BackgroundColorBox.h"

void TitleScene::Init()
{
	Scene::Init();
}

void TitleScene::Enter()
{
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("title_screen", "graphics/title_screen.png", true);

	sf::Vector2f resolutionSize = sf::Vector2f(WindowManager::GetInstance().GetResolutionSize());


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));


	RectSpriteGameObject* titleSprite = AddGameObject(new RectSpriteGameObject({ 1, 60, 176, 88 }, "title_screen", "TitleSprite"), LayerType::UI);
	titleSprite->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.3f });
	titleSprite->SetScale(sf::Vector2f::one * 5.f);

	MouseObject* mouse = AddGameObject(new MouseObject(), LayerType::UI);

	StartButton* button = AddGameObject(new StartButton("DungGeunMo", "Button", 100), LayerType::UI);

	button->SetOrigin(Origins::MiddleCenter);
	button->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.7f });
	button->SetString("Start Button");
	// button->SetScale({ 300.f, 300.f });
	button->SetButtonEvent(std::bind(&TitleScene::GameStart, this));

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

	if (isGameStart)
		SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
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

void TitleScene::GameStart()
{
	isGameStart = true;
}

TitleScene::TitleScene()
	: Scene(SceneIds::SceneDev2)
	, isGameStart(false)
{

}

TitleScene::~TitleScene()
{
}
