#pragma once
#include "ItemObject.h"

class MushRoomObject : public ItemObject
{
private:
	sf::Vector2f		moveDirection;
	float				moveSpeed;

public:
	void FixedUpdate(const float& deltaTime) override;

	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
public:
	MushRoomObject();
	~MushRoomObject() = default;
};

