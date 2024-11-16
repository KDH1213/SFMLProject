#pragma once

#include "SpriteGameObject.h"

class Player;

class BlockObject : public SpriteGameObject
{
protected:
	BlockType		type;
	Player*			player;

public:
	virtual void OnCollisionEnter(Collider* target);
	virtual void OnCollisionStay(Collider* target);
	virtual void OnCollisionEnd(Collider* target);

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	BlockObject(BlockType type, const std::string& texId, const std::string& name = "Block");
	virtual ~BlockObject() = default;
	BlockObject& operator= (const BlockObject& other) = delete;
};

