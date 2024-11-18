#include "stdafx.h"
#include "ItemBlockObject.h"

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
	return false;
}

bool ItemBlockObject::LoadCsv(const std::string& filePath)
{
	return false;
}
