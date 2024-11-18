#pragma once

#include "SaveData.h"

struct BlockSaveData
{
	GameObjectSaveData	gameObjectSaveData;

	int					type;
	sf::IntRect			textureUVRect;
	sf::Vector2f		rectSize;
	std::string			textureID;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(BlockSaveData, gameObjectSaveData, type, textureUVRect, rectSize, textureID);
};

struct ItemBlockSaveData
{
	GameObjectSaveData	gameObjectSaveData;
	BlockSaveData		blockSaveData;

	sf::IntRect			changeTextureUvRect;

	int					itemType;
	int					itemCount;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ItemBlockSaveData, gameObjectSaveData, blockSaveData, changeTextureUvRect, itemType, itemCount);
};