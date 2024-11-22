#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGameObject.h"
#include "UiTextGameObject.h"
#include "Test.h"

#include "Animation.h"
#include "Animator.h"

#include "Camera.h"
#include "CameraManger.h"

#include "TestPlayer.h"
#include "TileMap.h"

#include "Player.h"
#include "TileMapController.h"
#include "Goomba.h"
#include "BrickBlockObject.h"
#include "ItemBlockObject.h"
#include "Collider.h"

#include "PlayerSaveData.h"
#include "BlockSaveData.h"
#include "WallCollisionSaveData.h"
#include "WallCollisionObject.h"

#include "CoinObject.h"
#include "StarObject.h"
#include "FlowerObject.h"
#include "MushRoomObject.h"

#include "BackgroundColorBox.h"
#include "GameManager.h"
#include "SavePointObject.h"
#include "ImguiManger.h"
#include "GameClearObject.h"
#include "KoopaTroopa.h"

#include "InGameUIHub.h"
#include "EnemySpawner.h"
#include "Koopa.h"

void SceneDev2::Init()
{
	/*GameObject* obj = AddGameObject(new SpriteGameObject("Player"), RenderLayer::Default);


	obj->SetOrigin(Origins::MiddleCenter);
	obj->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });

	obj = AddGameObject(new UITextGameObject("KOMIKAP", "", 100), RenderLayer::Default);
	obj->SetOrigin(Origins::TopLeft);
	obj->SetPosition({ });
	((UITextGameObject*)obj)->SetString("SceneDev1");*/


	Scene::Init();
}

void SceneDev2::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	TEXTURE_MANAGER.Load("Player", "graphics/player.png");

	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");
	TEXTURE_MANAGER.Load("Items", "graphics/item_objects.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("tile_set", "graphics/tile_set.png");
	TEXTURE_MANAGER.Load("mario_bros", "graphics/mario_bros.png");

	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);

	Player* testPlayer = AddGameObject(new Player("Player"),LayerType::Player);
	testPlayer->Awake();
	mainCamera->SetFollowTarget(testPlayer, true);

	Koopa* koopa = AddGameObject(new Koopa(), LayerType::Enemy);
	koopa->Awake();
	koopa->SetPosition({300.f, 20.f});

	/*Goomba* enemy = AddGameObject(new Goomba(), LayerType::Enemy);
	enemy->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 500.f);

	KoopaTroopa* koopaTroopa = AddGameObject(new KoopaTroopa(), LayerType::Enemy);
	koopaTroopa->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 800.f);*/
	
	////auto animator = testPlayer->GetAnimator();
	////animator->AddAnimation(&ResourcesManager<Animation>::GetInstance().Get("marioIdle"), "marioIdle");

	//// Goomba* enemy = AddGameObject(new Goomba(), LayerType::Enemy);
	//// enemy->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 300.f);
	//// mainCamera->SetCameraLimitRect({ -2000.f, 2000.f, -2000.f, 2000.f });

	////TileMap* tile = AddGameObject(new TileMap("tiles", "Map"), LayerType::TileMap);
	////tile->SetTileInfo("tiles", { 30,30 }, { 64.f,64.f }, { 32,32 });
	////tile->SaveCsv("TileMap/test.csv");
	////tile->LoadCsv("TileMap/test.csv");
	//ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);

	////BlockObject* block = AddGameObject(new BlockObject(BlockType::Brick ,"tile_set"), LayerType::Block);

	//BrickBlockObject* brickBlock = AddGameObject(new BrickBlockObject("tile_set"), LayerType::Block); 
	//brickBlock->SetPosition({ 100.f, -150.f });

	WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	wallCollision->SetScale({ 10000.f, 30.f });
	wallCollision->SetPosition({ 0, 100.f });

	////  ItemBlockObject* block = AddGameObject(new ItemBlockObject(ItemType::MushRoom, "tile_set", "tile_set"), LayerType::Block);

	//TileMapController* tileMapController = AddGameObject(new TileMapController("TileMapController"), LayerType::Default);

	//CoinObject* coin = AddGameObject(new CoinObject, LayerType::Item);
	//coin->SetPosition({ -100.f, -150.f });
	//StarObject* star = AddGameObject(new StarObject, LayerType::Item);
	//star->SetPosition({ -150.f, -150.f });
	//FlowerObject* flower = AddGameObject(new FlowerObject, LayerType::Item);
	//flower->SetPosition({ -200.f, -150.f });
	//MushRoomObject* mushroom = AddGameObject(new MushRoomObject, LayerType::Item);
	//mushroom->SetPosition({ -250.f, -150.f });

	// InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

	EnemySpawner* enemySpawner = AddGameObject(new EnemySpawner(), LayerType::Default);
	enemySpawner->SetPosition({ 2000.f, 1300.f });

	/*GameClearObject* gameClearObject = AddGameObject(new GameClearObject(), LayerType::CleraPoint);
	gameClearObject->SetScale({ 10.f, 1300.f });
	gameClearObject->SetPosition({ 800.f, 0.f });
	gameClearObject->SetDestinationPosition({ 800.f, 440 });
	gameClearObject->SetMaxStartPosition({ 800.f, -440 });
	gameClearObject->SetEndMovePosition({ 1700.f, 440 });*/

	// SavePointObject* savePoint = AddGameObject(new SavePointObject(), LayerType::Default);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Block);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Wall);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);


	Scene::Enter();
}

void SceneDev2::Exit()
{
	TEXTURE_MANAGER.unLoad("player");
	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	/*if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space))
		SCENE_MANAGER.ChangeScene(SceneIds::SceneDev2);*/
}

void SceneDev2::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void SceneDev2::Save()
{
}

void SceneDev2::Load()
{
}

void SceneDev2::Save(const std::string& savePath)
{
}

void SceneDev2::Load(const std::string& loadPath)
{
}

SceneDev2::SceneDev2()
	: Scene(SceneIds::SceneDev2)
{

}

SceneDev2::~SceneDev2()
{
}
