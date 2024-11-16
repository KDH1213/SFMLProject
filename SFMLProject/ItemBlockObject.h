#pragma once
#include "BlockObject.h"

class ItemBlockObject : public BlockObject
{
protected:
	std::string		changeTextureID;
	ItemType		itemType;
	int				itemCount;

public:
	ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name = "ItemBlock");
	virtual ~ItemBlockObject() = default;
	ItemBlockObject& operator= (const ItemBlockObject& other) = delete;
};

