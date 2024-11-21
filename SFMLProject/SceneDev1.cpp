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

#include "CoinObject.h"
#include "StarObject.h"
#include "FlowerObject.h"
#include "MushRoomObject.h"

#include "BackgroundColorBox.h"
#include "GameManager.h"
#include "SavePointObject.h"
#include "ImguiManger.h"
#include "GameClearObject.h"

#include "InGameUIHub.h"


void SceneDev1::Init()
{
	Scene::Init();

	cameraLimitRect = { 0.f,13440.f,-500.f, 700.f };
	currentCameraLimitRect = cameraLimitRect;
}

void SceneDev1::Enter()
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

	ResourcesManager<Animation>::GetInstance().Load("marioIdle", "animations/marioIdle.csv");

	//Player* testPlayer = AddGameObject(new Player("Player"),LayerType::Player);
	//testPlayer->Awake();
	////testPlayer->CreateAnimator();

	////auto animator = testPlayer->GetAnimator();
	////animator->AddAnimation(&ResourcesManager<Animation>::GetInstance().Get("marioIdle"), "marioIdle");
	//mainCamera->SetFollowTarget(testPlayer, true);

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

	//WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	//wallCollision->SetScale({ 10000.f, 30.f });
	//wallCollision->SetPosition({ 0, 100.f });

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

	InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

	/*GameClearObject* gameClearObject = AddGameObject(new GameClearObject(), LayerType::CleraPoint);
	gameClearObject->SetScale({ 10.f, 1300.f });
	gameClearObject->SetPosition({ 800.f, 0.f });
	gameClearObject->SetDestinationPosition({ 800.f, 440 });
	gameClearObject->SetMaxStartPosition({ 800.f, -440 });
	gameClearObject->SetEndMovePosition({ 1700.f, 440 });*/

	SavePointObject* savePoint = AddGameObject(new SavePointObject(), LayerType::Default);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Block);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Wall);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);
	
	if (GameManager::GetInstance().IsRestart())
	{
		// GameManager::GetInstance().OnSavePoint();

	}
	else
	{
		Load();
		// SaveLoadManager::GetInstance().Load();
		//GameManager::GetInstance().OnSavePoint();
	}
	Scene::Enter();


	GameManager::GetInstance().SetTimerUI(uiHub->GetTextGameObject("TimerUI"));
	GameManager::GetInstance().SetCoinUI(uiHub->GetTextGameObject("CoinUI"));
	GameManager::GetInstance().SetScoreUI(uiHub->GetTextGameObject("ScoreUI"));
	uiHub->GetTextGameObject("WorldUI")->SetString(GameManager::GetInstance().GetWorldName());

	GameManager::GetInstance().GameStartInit();
}

void SceneDev1::Exit()
{
	ImguiManger::GetInstance().Reset();
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

	if (GameManager::GetInstance().IsRestart())
	{
		ColliderManager::GetInstance().Clear();
		GameManager::GetInstance().ReStart();
		player = nullptr;
	}
	else
	{
		GameManager::GetInstance().Update(dt);
	}

	if (player != nullptr)
	{
		currentCameraLimitRect.leftPosition = player->GetPosition().x - 800.f;
		currentCameraLimitRect.leftPosition = currentCameraLimitRect.leftPosition < 0.f ? 0.f : currentCameraLimitRect.leftPosition;
		mainCamera->SetCameraLimitRect(currentCameraLimitRect);
	}


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
				continue;
			}

			auto wallCollision = dynamic_cast<WallCollisionObject*>(gameObject);
			if (wallCollision != nullptr)
			{
				data.wallCollisionSaveDatas.push_back(wallCollision->GetWallCollisionSaveData());
				continue;
			}

			auto blockObject = dynamic_cast<BlockObject*>(gameObject);
			if (blockObject != nullptr)
			{

				if (blockObject->GetBlockType() == BlockType::Item || blockObject->GetBlockType() == BlockType::ItemBrick)
				{
					data.itemBlockSaveDatas.push_back(((ItemBlockObject*)blockObject)->GetItemBlockSaveData());
				}
				else
				{
					data.blockSaveDatas.push_back(blockObject->GetBlockSaveDate());
				}
				continue;
			}

			auto savePoint = dynamic_cast<SavePointObject*>(gameObject);
			if (savePoint != nullptr)
			{
				data.savePointSaveDatas.push_back(savePoint->GetSavePointSaveData());
				continue;
			}

		}
	}
	SaveLoadManager::GetInstance().Save(data);
}

void SceneDev1::Load()
{
	SaveDataVC data = SaveLoadManager::GetInstance().Load();

	Player* player = new Player();	
	this->player = player;
	player->LoadData(data.playerData);
	player->Start();
	AddGameObject(player, player->GetLayerType());
	mainCamera->SetCameraLimitRect({ 0.f,13440.f,-500.f, 700.f }, true);
	mainCamera->SetFollowTarget(player, true);
	mainCamera->SetCameraPosition(player->GetPosition());


	for (const auto& data : data.blockSaveDatas)
	{
		BlockObject* newBlock = nullptr;
		switch ((BlockType)data.blockType)
		{
		case BlockType::Default:
		{
			newBlock = new BlockObject(BlockType::Default, "");
		}
			break;
		case BlockType::Brick:
			newBlock = new BrickBlockObject("");
			break;
		case BlockType::Secret:
			break;
		case BlockType::ItemBrick:
			// newBlock = new BrickBlockObject("");
			break;
		default:
			break;
		}

		if (newBlock == nullptr)
			continue;


		newBlock->LoadBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, newBlock->GetLayerType());
	}

	for (const auto& data : data.itemBlockSaveDatas)
	{
		ItemBlockObject* newBlock = new ItemBlockObject(ItemType::Coin, "", "");
		newBlock->LoadItemBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, newBlock->GetLayerType());
	}

	for (const auto& data : data.wallCollisionSaveDatas)
	{
		WallCollisionObject* wall = new WallCollisionObject();
		wall->LoadWallCollisionSaveData(data);
		wall->Start();
		AddGameObject(wall, wall->GetLayerType());
	}


	TileMapController* tileMapController = new TileMapController("");
	tileMapController->LoadTileMapSaveData(data.tileMapSaveData);
	tileMapController->Start();
	AddGameObject(tileMapController, tileMapController->GetLayerType());
}

void SceneDev1::Save(const std::string& savePath)
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
				continue;
			}

			auto wallCollision = dynamic_cast<WallCollisionObject*>(gameObject);
			if (wallCollision != nullptr)
			{
				data.wallCollisionSaveDatas.push_back(wallCollision->GetWallCollisionSaveData());
				continue;
			}

			auto blockObject = dynamic_cast<BlockObject*>(gameObject);
			if (blockObject != nullptr)
			{

				if (blockObject->GetBlockType() == BlockType::Item || blockObject->GetBlockType() == BlockType::ItemBrick)
				{
					data.itemBlockSaveDatas.push_back(((ItemBlockObject*)blockObject)->GetItemBlockSaveData());
				}
				else
				{
					data.blockSaveDatas.push_back(blockObject->GetBlockSaveDate());
				}
				continue;
			}

			auto savePoint = dynamic_cast<SavePointObject*>(gameObject);
			if (savePoint != nullptr)
			{
				data.savePointSaveDatas.push_back(savePoint->GetSavePointSaveData());
				continue;
			}
		}
	}
	SaveLoadManager::GetInstance().Save(data, savePath);
}

void SceneDev1::Load(const std::string& loadPath)
{
	SaveDataVC data = SaveLoadManager::GetInstance().Load(loadPath);

	Player* player = new Player();
	this->player = player;
	player->LoadData(data.playerData);
	player->Start();
	AddGameObject(player, player->GetLayerType());

	mainCamera->SetFollowTarget(player, true);
	mainCamera->SetCameraLimitRect(cameraLimitRect, true);

	for (const auto& data : data.blockSaveDatas)
	{
		BlockObject* newBlock = nullptr;
		switch ((BlockType)data.blockType)
		{
		case BlockType::Default:
		{
			newBlock = new BlockObject(BlockType::Default, "");
		}
		break;
		case BlockType::Brick:
			newBlock = new BrickBlockObject("");
			break;
		case BlockType::Secret:
			break;
		case BlockType::ItemBrick:
			// newBlock = new BrickBlockObject("");
			break;
		default:
			break;
		}

		if (newBlock == nullptr)
			continue;


		newBlock->LoadBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, newBlock->GetLayerType());
	}

	for (const auto& data : data.itemBlockSaveDatas)
	{
		ItemBlockObject* newBlock = new ItemBlockObject(ItemType::Coin, "", "");
		newBlock->LoadItemBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, newBlock->GetLayerType());
	}

	for (const auto& data : data.wallCollisionSaveDatas)
	{
		WallCollisionObject* wall = new WallCollisionObject();
		wall->LoadWallCollisionSaveData(data);
		wall->Start();
		AddGameObject(wall, wall->GetLayerType());
	}


	TileMapController* tileMapController = new TileMapController("");
	tileMapController->LoadTileMapSaveData(data.tileMapSaveData);
	tileMapController->Start();
	AddGameObject(tileMapController, tileMapController->GetLayerType());
}

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
{

}

SceneDev1::~SceneDev1()
{
}
