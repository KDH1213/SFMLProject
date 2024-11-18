#pragma once
#include "BlockObject.h"

class ItemBlockObject : public BlockObject
{
protected:
	sf::IntRect		changeTextureUvRect;

	ItemType		itemType;
	int				itemCount;

public:
	virtual void SetChangeTextureUvRect(const sf::IntRect uvRect) { changeTextureUvRect = uvRect; }
	virtual sf::IntRect GetChangeTextureUvRect() { return changeTextureUvRect; }

	void SetItemType(ItemType type) { itemType = type; }
	ItemType GetItemType() { return itemType; }

public:
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name = "ItemBlock");
	virtual ~ItemBlockObject() = default;
	ItemBlockObject& operator= (const ItemBlockObject& other) = delete;
};

