#pragma once

#include "ItemObject.h"

class StarObject : public ItemObject
{
private:
	sf::Vector2f		moveDirection;
	float				moveSpeed;

public:
	void FixedUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
public:
	StarObject();
	~StarObject() = default;
};

