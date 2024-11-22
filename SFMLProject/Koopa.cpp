#include "stdafx.h"
#include "Koopa.h"

#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Rigidbody.h"
#include "KoopaFSM.h"

Koopa::Koopa(const std::string& name)
	: Enemy(name)
	, player(nullptr)
	, currentJumpTime(0.f)
	, jumpTime(3.f)
	, isJump(false)


{
	fsm = new KoopaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/koopa.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

Koopa::~Koopa()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void Koopa::OnJump()
{
	isJump = true;
	rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x  , -900.f});
	rigidBody->SetGround(false);
	currentJumpTime = 0.f;
}

void Koopa::Awake()
{
	// animator->ChangeAnimation("goombaMove", true);
}

void Koopa::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Idle);
	GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });

	player = (Player*)(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));
}

void Koopa::Update(const float& deltaTime)
{
	Enemy::Update(deltaTime);

	float distance = abs(abs(player->GetPosition().x) - abs(position.x));
	if (distance < 400.f)
	{
		if (position.x < player->GetPosition().x)
			rigidBody->SetVelocity({ -currentStatus.speed , rigidBody->GetCurrentVelocity().y });
		else
			rigidBody->SetVelocity({ currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
	}
	else
	{
		if (position.x < player->GetPosition().x)
			rigidBody->SetVelocity({ currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
		else
			rigidBody->SetVelocity({ -currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
	}

	if (!isJump)
	{
		currentJumpTime += deltaTime;

		if (currentJumpTime >= jumpTime)
			OnJump();
	}

	if (isJump && rigidBody->IsGround())
		isJump = false;
}

void Koopa::OnCollisionEnter(Collider* target)
{
}

void Koopa::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		((Player*)target->GetOwner())->TakeDamage();
	}
}

void Koopa::OnCollisionEnd(Collider* target)
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