#include "stdafx.h"
#include "StarObject.h"
#include "Rigidbody.h"

StarObject::StarObject()
	: ItemObject(ItemType::Star, "Items", "Star")
	, moveSpeed(500.f)
	, moveDirection(sf::Vector2f::right)
{
	rigidBody = new Rigidbody(this);
}

void StarObject::FixedUpdate(const float& deltaTime)
{
}

void StarObject::OnCollisionEnter(Collider* target)
{
}

void StarObject::OnCollisionStay(Collider* target)
{
}

void StarObject::OnCollisionEnd(Collider* target)
{
}
