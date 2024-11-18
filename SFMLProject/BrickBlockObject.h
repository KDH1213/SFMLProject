#pragma once
#include "BlockObject.h"
class BrickBlockObject : public BlockObject
{
public:
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

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

