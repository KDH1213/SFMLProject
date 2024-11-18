#include "stdafx.h"
#include "SceneDev1.h"
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

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	TEXTURE_MANAGER.Load("Player", "graphics/player.png");

	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");

	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");
	TEXTURE_MANAGER.Load("Items", "graphics/Items.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("tile_set", "graphics/tile_set.png");
	TEXTURE_MANAGER.Load("mario_bros", "graphics/mario_bros.png");

	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	ResourcesManager<Animation>::GetInstance().Load("marioIdle", "animations/marioIdle.csv");

	Player* testPlayer = AddGameObject(new Player("Player"),LayerType::Player);
	testPlayer->Awake();
	testPlayer->GetCollider()->SetScale({ 100.f, 150.f });
	//testPlayer->CreateAnimator();

	//auto animator = testPlayer->GetAnimator();
	//animator->AddAnimation(&ResourcesManager<Animation>::GetInstance().Get("marioIdle"), "marioIdle");
	mainCamera->SetFollowTarget(testPlayer, true);

	Goomba* enemy = AddGameObject(new Goomba(), LayerType::Enemy);
	enemy->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 20.f);
	// mainCamera->SetCameraLimitRect({ -2000.f, 2000.f, -2000.f, 2000.f });

	//TileMap* tile = AddGameObject(new TileMap("tiles", "Map"), LayerType::TileMap);
	//tile->SetTileInfo("tiles", { 30,30 }, { 64.f,64.f }, { 32,32 });
	//tile->SaveCsv("TileMap/test.csv");
	//tile->LoadCsv("TileMap/test.csv");
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);

	BlockObject* block = AddGameObject(new BlockObject(BlockType::Brick ,"tile_set"), LayerType::Block);

	BrickBlockObject* brickBlock = AddGameObject(new BrickBlockObject("tile_set"), LayerType::Block);
	brickBlock->SetPosition({ 100.f, -150.f });
	//  ItemBlockObject* block = AddGameObject(new ItemBlockObject(ItemType::MushRoom, "tile_set", "tile_set"), LayerType::Block);

	TileMapController* tileMapController = AddGameObject(new TileMapController("TileMapController"), LayerType::Default);


	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Player);
	Scene::Enter();
}

void SceneDev1::Exit()
{
	TEXTURE_MANAGER.unLoad("player");
	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	Scene::Exit();

	CameraManger::GetInstance().Clear();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev1::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void SceneDev1::Save()
{
	SaveDataVC data;

	data.playerData = ((Player*)FindGameObject("Player"))->GetPlayerSaveData();

	for (auto& gameObjects : gameObjectVectors)
	{
		for (auto& gameObject : gameObjects)
		{
			auto tileMapController = dynamic_cast<TileMapController*>(gameObject);
			if (tileMapController != nullptr)
			{
				data.tileMapSaveData = tileMapController->GetTileMapSaveData();
			}

			auto wallCollision = dynamic_cast<WallCollisionObject*>(gameObject);
			if (wallCollision != nullptr)
			{
				data.wallCollisionSaveDatas.push_back(wallCollision->GetWallCollisionSaveData());
			}

			auto blockObject = dynamic_cast<BlockObject*>(gameObject);
			if (wallCollision != nullptr)
			{
				data.blockSaveDatas.push_back(blockObject->GetBlockSaveDate());
			}
		}
	}
	SaveLoadManager::GetInstance().Save(data);
}

void SceneDev1::Load()
{
	SaveDataVC data = SaveLoadManager::GetInstance().Load();

	Player* player = new Player();
	player->LoadData(data.playerData);
	player->Start();
	AddGameObject(player, LayerType::Player);

	for (const auto& data : data.blockSaveDatas)
	{
		BlockObject* newBlock = new BlockObject(BlockType::Default, "");
		newBlock->LoadBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, LayerType::Block);
	}

	TileMapController* tileMapController = new TileMapController("");
	tileMapController->LoadTileMapSaveData(data.tileMapSaveData);

	tileMapController->Start();
	AddGameObject(tileMapController, LayerType::Default);
}

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
{

}

SceneDev1::~SceneDev1()
{
}
