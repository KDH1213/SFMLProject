#include "stdafx.h"
#include "ItemBlockObject.h"

ItemBlockObject::ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name)
	: BlockObject(BlockType::Item, texId, name)
	, changeTextureID(changeTexId)
	, itemType(type)
	, itemCount(1)
{
}
