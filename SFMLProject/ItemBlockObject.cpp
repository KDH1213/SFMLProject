#include "stdafx.h"
#include "ItemBlockObject.h"
#include "rapidcsv.h"

ItemBlockObject::ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name)
	: BlockObject(BlockType::Item, texId, name)
	, itemType(type)
	, itemCount(1)
	, changeTextureUvRect(0, 0, 16, 16)
{
}

void ItemBlockObject::OnCollisionEnter(Collider* target)
{
}

void ItemBlockObject::OnCollisionStay(Collider* target)
{
}

void ItemBlockObject::OnCollisionEnd(Collider* target)
{
}

bool ItemBlockObject::Save() const
{
	return false;
}

bool ItemBlockObject::Load()
{
	return false;
}

bool ItemBlockObject::SaveCsv(const std::string& filePath) const
{
	std::ofstream outFile(filePath);

	outFile << "OBJECTNAME, TEXTUREID, BLOCK TPYE, RECTSIZEX,RECTSIZEX, TEXTUREUVRECT LEFT, TEXTUREUVRECT TOP, TEXTUREUVRECT WIDTH, TEXTUREUVRECT HEIGHT" << std::endl;

	outFile << name;
	outFile << "," + textureID;
	outFile << "," + std::to_string((int)type);
	outFile << "," + std::to_string(rectSize.x);
	outFile << "," + std::to_string(rectSize.y);

	outFile << "," + std::to_string(textureUVRect.left);
	outFile << "," + std::to_string(textureUVRect.top);
	outFile << "," + std::to_string(textureUVRect.width);
	outFile << "," + std::to_string(textureUVRect.height) << std::endl;

	outFile << "ITEMTYPE, ITEMCOUNT, TEXTUREUVRECT LEFT, TEXTUREUVRECT TOP, TEXTUREUVRECT WIDTH, TEXTUREUVRECT HEIGHT" << std::endl;

	outFile << std::to_string((int)itemType);
	outFile << "," + std::to_string((int)itemCount);
	outFile << "," + std::to_string(changeTextureUvRect.left);
	outFile << "," + std::to_string(changeTextureUvRect.top);
	outFile << "," + std::to_string(changeTextureUvRect.width);
	outFile << "," + std::to_string(changeTextureUvRect.height);
	return true;
}

bool ItemBlockObject::LoadCsv(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	name = doc.GetCell<std::string>(0, 0);
	textureID = doc.GetCell<std::string>(1, 0);
	type = (BlockType)doc.GetCell<int>(2, 0);
	rectSize.x = doc.GetCell<float>(3, 0);
	rectSize.y = doc.GetCell<float>(4, 0);
	textureUVRect.left = doc.GetCell<int>(5, 0);
	textureUVRect.top = doc.GetCell<int>(6, 0);
	textureUVRect.width = doc.GetCell<int>(7, 0);
	textureUVRect.height = doc.GetCell<int>(8, 0);

	itemType = (ItemType)doc.GetCell<int>(0, 2);
	itemCount = doc.GetCell<int>(1, 2);
	changeTextureUvRect.left = doc.GetCell<int>(2, 2);
	changeTextureUvRect.top = doc.GetCell<int>(3, 2);
	changeTextureUvRect.width = doc.GetCell<int>(4, 2);
	changeTextureUvRect.height = doc.GetCell<int>(5, 2);

	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID));
	render.setTextureRect(textureUVRect);
	SetScale(scale);
	return true;
}

ItemBlockSaveData ItemBlockObject::GetItemBlockSaveData() const
{
	return ItemBlockSaveData({ GetGameObjectSaveData(), GetBlockSaveDate(), changeTextureUvRect, (int)itemType ,itemCount });
}

void ItemBlockObject::LoadItemBlockSaveData(const ItemBlockSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	LoadBlockSaveData(data.blockSaveData);

	changeTextureUvRect = data.changeTextureUvRect;
	itemType = (ItemType)data.itemType;
	itemCount = data.itemCount;
}
