#pragma once
#include "BlockObject.h"
class BrickBlockObject : public BlockObject
{
public:
	virtual void OnCollisionEnter(Collider* target);
	virtual void OnCollisionStay(Collider* target);
	virtual void OnCollisionEnd(Collider* target);

public:
	BrickBlockObject(const std::string& texId, const std::string& name = "BrickBlock");
	virtual ~BrickBlockObject() = default;
	BrickBlockObject& operator= (const BrickBlockObject& other) = delete;
};

