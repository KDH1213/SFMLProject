#pragma once

namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2u, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::IntRect, left, top, width, height);
}

#include "PlayerSaveData.h"
#include "BlockSaveData.h"
#include "WallCollisionSaveData.h"
#include "TileMapSaveData.h"

struct SaveData
{
public:
	int version = 0;
	PlayerSaveData						playerData;
	std::vector<BlockSaveData>			blockSaveDatas;
	std::vector<ItemBlockSaveData>		itemBlockSaveDatas;
	std::vector<WallCollisionSaveData>	wallCollisionSaveDatas;
	TileMapSaveData						tileMapSaveData;

	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{
public:

public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, version, playerData, blockSaveDatas, itemBlockSaveDatas, wallCollisionSaveDatas, tileMapSaveData);

public:
	SaveDataV1() { version = 1; }
};

struct SaveDataV2 : public SaveData
{
public:
	// std::vector<SaveZombie> zombies;

public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version);
	// NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version, highscore, gold, zombies);
public:
	SaveDataV2() { version = 2; }
};


typedef SaveDataV1 SaveDataVC;
