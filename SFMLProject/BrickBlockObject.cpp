#include "stdafx.h"
#include "BrickBlockObject.h"
#include "Collider.h"
#include "Player.h"
#include "Rigidbody.h"

BrickBlockObject::BrickBlockObject(const std::string& texId, const std::string& name)
	: BlockObject(BlockType::Brick, texId, name)
{
}

void BrickBlockObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = (target->GetOwner()->GetRigidbody()->GetCurrentVelocity().y + target->GetOwner()->GetRigidbody()->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime() * player->GetSpeed();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			player->GetRigidbody()->SetGround(true);
			player->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
			SetDestory(true);
	}
}

void BrickBlockObject::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Rigidbody* targetRigidbody = player->GetRigidbody();

		if (!targetRigidbody->IsGround())
		{
			if(position.x < player->GetPosition().x && player->GetRigidbody()->GetCurrentVelocity().x < 0.f)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (position.x > player->GetPosition().x && player->GetRigidbody()->GetCurrentVelocity().x > 0.f)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
	}

	/*if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Enemy
		|| target->GetColliderLayer() == ColliderLayer::Block)
	{

	}*/
}

void BrickBlockObject::OnCollisionEnd(Collider* target)
{
}

bool BrickBlockObject::Save() const
{
	return false;
}

bool BrickBlockObject::Load()
{
	return false;
}

bool BrickBlockObject::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool BrickBlockObject::LoadCsv(const std::string& filePath)
{
	return false;
}
