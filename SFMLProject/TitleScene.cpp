#include "stdafx.h"
#include "TitleScene.h"

#include "RectSpriteGameObject.h"
#include "MouseObject.h"
#include "UIButtonObject.h"
#include "TextButton.h"
#include "BackgroundColorBox.h"
#include "Collider.h"

#include "FadeOutUI.h"

void TitleScene::Init()
{
	Scene::Init();
}

void TitleScene::Enter()
{
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("title_screen", "graphics/title_screen.png", true);


	fadeOutUI = AddGameObject(new FadeOutUI("FadeOut"), LayerType::UI);
	fadeOutUI->SetScale({ 3000.f, 3000.f });
	fadeOutUI->SetPosition({ 1000.f,1000.f });
	//fadeOut->SetOrigin(Origins)
	//fadeOutUI->SetActive(false);
	fadeOutUI->AddFadeOutEndEvent(std::bind(&TitleScene::StartGame, this));
	sf::Vector2f resolutionSize = sf::Vector2f(WindowManager::GetInstance().GetResolutionSize());


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));


	RectSpriteGameObject* titleSprite = AddGameObject(new RectSpriteGameObject({ 1, 60, 176, 88 }, "title_screen", "TitleSprite"), LayerType::InGameUI);
	titleSprite->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.3f });
	titleSprite->SetScale(sf::Vector2f::one * 5.f);

	MouseObject* mouse = AddGameObject(new MouseObject(), LayerType::UI);

	TextButton* button = AddGameObject(new TextButton("DungGeunMo", "Start Button", 100), LayerType::InGameUI);
	button->SetOrigin(Origins::MiddleCenter);
	button->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.6f });
	button->SetString("Start Button");
	button->SetButtonClickEvent(std::bind(&FadeOutUI::StartFadeOut, fadeOutUI));
	button->GetCollider()->SetOffsetPosition({ 0.f, 50.f });

	TextButton* endButton = AddGameObject(new TextButton("DungGeunMo", "End Button", 100), LayerType::InGameUI);
	endButton->SetOrigin(Origins::MiddleCenter);
	endButton->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.75f });
	endButton->SetString("End Button");
	endButton->SetButtonClickEvent(std::bind(&TitleScene::EndGame, this));
	endButton->GetCollider()->SetOffsetPosition({ 0.f, 50.f });

	CollisitionCheck();

	Scene::Enter();

	// fadeOutUI->SetActive(false);
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

	if (isStartGame)
		SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
}

void TitleScene::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void TitleScene::Save(const std::string& savePath)
{
}

void TitleScene::Load(const std::string& loadPath)
{
}

void TitleScene::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
}

void TitleScene::StartGame()
{
	isStartGame = true;
}

void TitleScene::EndGame()
{
	isEndGame = true;
	WindowManager::GetInstance().GetRenderWindow()->close();
}

TitleScene::TitleScene()
	: Scene(SceneIds::SceneDev2)
	, isStartGame(false)
	, isEndGame(false)
	, fadeOutUI(nullptr)
{

}

TitleScene::~TitleScene()
{
}
