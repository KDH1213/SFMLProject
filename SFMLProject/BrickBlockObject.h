#pragma once
#include "BlockObject.h"
class BrickBlockObject : public BlockObject
{
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
	BrickBlockObject(const std::string& texId, const std::string& name = "BrickBlock");
	virtual ~BrickBlockObject() = default;
	BrickBlockObject& operator= (const BrickBlockObject& other) = delete;
};

