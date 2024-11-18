#include "stdafx.h"
#include "Goomba.h"

#include "Animator.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Rigidbody.h"

Goomba::Goomba(const std::string& name)
	: Enemy(name)
{
	fsm = new GoombaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/goomba.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

Goomba::~Goomba()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void Goomba::Awake()
{
	animator->ChangeAnimation("goombaMove", true);
}

void Goomba::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Scout);
}

void Goomba::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Player* player = (Player*)target->GetOwner();
		
		sf::Vector2f targetPosition = target->GetPosition();
		
		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = (target->GetOwner()->GetRigidbody()->GetCurrentVelocity().y + target->GetOwner()->GetRigidbody()->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime() * player->GetSpeed();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			fsm->ChangeState(EnemyStateType::Dead);
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
			player->TakeDamage();
		else
			player->TakeDamage();		
	}
	else if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Enemy
		|| target->GetColliderLayer() == ColliderLayer::Block)
		fsm->ChangeState(EnemyStateType::Chase);
}

void Goomba::OnCollisionStay(Collider* target)
{
}

void Goomba::OnCollisionEnd(Collider* target)
{
}
