#include "stdafx.h"
#include "BrickBlockObject.h"
#include "Collider.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Enemy.h"

BrickBlockObject::BrickBlockObject(const std::string& texId, const std::string& name)
	: BlockObject(BlockType::Brick, texId, name)
	, isHit(false)
	, hitMoveDistance(32.f)
	, moveSpeed(500.f)
	, isReturn(false)
	, currentMoveTime(0.f)
{
}

void BrickBlockObject::OnBreak()
{
	SetDestory(true);
}

void BrickBlockObject::OnHitMove()
{
	if (!isHit)
	{
		isHit = true;
		startPosition = position;
		endPosition = position;
		endPosition.y -= hitMoveDistance;
		currentMoveTime = 0.f;
	}

	isReturn = false;
}

void BrickBlockObject::Update(const float& deltaTime)
{
	if (isHit)
	{
		position.y += moveSpeed * deltaTime * (isReturn ? 1.f : -1.f);
		// currentMoveTime += deltaTime;

		if (!isReturn)
		{
			if (position.y <= endPosition.y)
			{
				position.y = endPosition.y;
				isReturn = true;
			}
		}
		else
		{
			if (position.y >= startPosition.y)
			{
				position.y = startPosition.y;
				isHit = false;
			}
		}

		SetPosition(position);
	}
}

void BrickBlockObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = player->GetRigidbody()->GetCurrentVelocity().y * TimeManager::GetInstance().GetFixedDeletaTime();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			player->GetRigidbody()->SetGround(true);
			player->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
		{
			player->SetPosition({ player->GetPosition().x, rect.bottomPosition + target->GetScale().y * 0.5f });
			player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x , 0.f });

			if (abs(position.x - player->GetPosition().x) < 56.f)
			{
				auto targets = collider->GetCollisionTargets();

				for (auto& target : targets)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(target);
					if (enemy != nullptr)
					{
						enemy->SetHitDirection(enemy->GetPosition().x < position.x ? sf::Vector2f::left : sf::Vector2f::right);
						enemy->TakeDamage();
					}
				}
				if (player->GetCurrentHP() == 1)
					OnHitMove();
				else
					SetDestory(true);
			}

		}
	}
}

void BrickBlockObject::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Rigidbody* targetRigidbody = player->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		sf::Vector2f prevPosition = player->GetRigidbody()->GetCurrentVelocity() * TimeManager::GetInstance().GetFixedDeletaTime();


		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{
			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				{
					player->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				{
					player->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
			}
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