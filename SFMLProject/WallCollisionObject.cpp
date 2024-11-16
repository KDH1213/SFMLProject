#include "stdafx.h"
#include "WallCollisionObject.h"
#include "Collider.h"
#include "Collision.h"

int WallCollisionObject::wallID = 0;

WallCollisionObject::WallCollisionObject(const std::string& name)
    : GameObject(name + std::to_string(wallID++))
{
    originPreset = Origins::MiddleCenter;
    CreateCollider(ColliderType::Rectangle, ColliderLayer::Wall);
}

WallCollisionObject::~WallCollisionObject()
{
}


void WallCollisionObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	collider->SetOwnerScale(scale);
}

void WallCollisionObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collider->SetPosition(position);
}

void WallCollisionObject::SetOrigin(Origins preset)
{
	originPreset = preset;
    collider->SetOrigin(preset);
}

sf::FloatRect WallCollisionObject::GetLocalBounds() const
{
    return collider->GetLocalBounds();
}

sf::FloatRect WallCollisionObject::GetGlobalBounds() const
{
    return collider->GetGlobalBounds();
}
void WallCollisionObject::Start()
{
	collider->Reset();
}

void WallCollisionObject::OnCollisionEnter(Collider* target)
{
}

void WallCollisionObject::OnCollisionStay(Collider* target)
{
}

void WallCollisionObject::OnCollisionEnd(Collider* target)
{
}

bool WallCollisionObject::Save() const
{
    return false;
}

bool WallCollisionObject::Load()
{
    return false;
}

bool WallCollisionObject::SaveCsv(const std::string& filePath) const
{
    return false;
}

bool WallCollisionObject::LoadCsv(const std::string& filePath)
{
    return false;
}
