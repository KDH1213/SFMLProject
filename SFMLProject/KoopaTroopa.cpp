#include "stdafx.h"
#include "KoopaTroopa.h"

#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Animation.h"

KoopaTroopa::KoopaTroopa(const std::string& name)
{
	// fsm = new GoombaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/goomba.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

KoopaTroopa::~KoopaTroopa()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void KoopaTroopa::Awake()
{
	animator->ChangeAnimation("goombaMove", true);
}

void KoopaTroopa::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Scout);

	GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
}

void KoopaTroopa::OnCollisionEnter(Collider* target)
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
			TakeDamage();
			player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x, 100.f });
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

void KoopaTroopa::OnCollisionStay(Collider* target)
{
}

void KoopaTroopa::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
	{
		auto& targets = collider->GetCollisionTargets();
		bool isGround = false;
		for (auto& targetCollsion : targets)
		{
			if (targetCollsion == target)
				continue;

			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetCollsion->GetPosition(), targetCollsion->GetScale());

			if (rect.bottomPosition == targetRect.topPosition)
			{
				isGround = true;
				break;
			}
		}

		if (!isGround)
			rigidBody->SetGround(false);
	}
}