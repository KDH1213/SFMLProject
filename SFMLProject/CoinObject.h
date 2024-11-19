#pragma once
#include "ItemObject.h"
class CoinObject : public ItemObject
{
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void CreateAnimator() override;

public:
	CoinObject();
	~CoinObject() = default;
};