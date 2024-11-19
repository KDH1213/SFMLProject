#include "stdafx.h"
#include "MushRoomObject.h"
#include "Rigidbody.h"
#include "Collider.h"

MushRoomObject::MushRoomObject()
	: ItemObject(ItemType::MushRoom, "Items", "MushRoom")
	, moveDirection(sf::Vector2f::right)
	, moveSpeed(200.f)
{
	textureUVRect = { 0,0,16,16 };
	scale = { 2.f,2.f };
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(true);
}



void MushRoomObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	sprite.setTextureRect(textureUVRect);

	SetOrigin(originPreset);
	collider->Reset();
	collider->SetScale({ 32.f,32.f });
}

void MushRoomObject::FixedUpdate(const float& deltaTime)
{
	if (!isCreateEvent)
	{
		rigidBody->SetVelocity({ speed * moveDirection.x,  rigidBody->GetCurrentVelocity().y});
	}
	rigidBody->FixedUpdate(deltaTime);
}

void MushRoomObject::OnCollisionStay(Collider* target)
{
}

void MushRoomObject::OnCollisionEnd(Collider* target)
{
}
