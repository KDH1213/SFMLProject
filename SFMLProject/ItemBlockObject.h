#pragma once
#include "BlockObject.h"

class ItemBlockObject : public BlockObject
{
protected:
	sf::IntRect		changeTextureUvRect;

	ItemType		itemType;
	int				itemCount;

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name = "ItemBlock");
	virtual ~ItemBlockObject() = default;
	ItemBlockObject& operator= (const ItemBlockObject& other) = delete;
};

