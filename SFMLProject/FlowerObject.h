#pragma once
#include "ItemObject.h"
class FlowerObject : public ItemObject
{
public:
	void Start() override;

public:
	FlowerObject();
	~FlowerObject() = default;
};

