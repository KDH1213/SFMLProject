#include "stdafx.h"
#include "GoombaDeadState.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
GoombaDeadState::GoombaDeadState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
	, rotationTime(0.3f)
	, currentRotationTime(0.f)
	, currentTime(0.f)
	, isJumpDie(false)
	, isEndRotation(false)
	, jumpDeadTime(0.3f)
{	
}

GoombaDeadState::~GoombaDeadState()
{
}

void GoombaDeadState::IsJumpDie(float deltaTime)
{
	currentTime += deltaTime;

	if (currentTime >= jumpDeadTime)
		enemy->OnDestory();
}

void GoombaDeadState::IsHitDie(float deltaTime)
{
	if (!isEndRotation)
	{
		currentRotationTime += deltaTime;
		float rotation = enemy->GetRotation();

		rotation = Utils::Lerp(rotation, 180.f, currentRotationTime / rotationTime);
		enemy->SetRotation(rotation);

		if (currentRotationTime >= rotationTime)
		{
			isEndRotation = true;
			rigidbody->SetVelocity({ hitDirection.x * 200.f , rigidbody->GetCurrentVelocity().y });
		}
	}

	if (enemy->GetPosition().y >= 2000.f)
		enemy->OnDestory();
}

void GoombaDeadState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void GoombaDeadState::Start()
{
}

void GoombaDeadState::Enter()
{
	rigidbody->ResetVelocity();
	rigidbody->SetGround(false);
	enemy->GetCollider()->SetActive(false);


	if (enemy->IsJumpHitDead())
	{
		isJumpDie = true;
		rigidbody->SetActive(false);
		enemy->GetAnimator()->ChangeAnimation("goombaDead");
	}
	else
	{
		hitDirection = enemy->GetHitDirection();
		currentRotationTime = 0.f;
		rigidbody->SetVelocity({ hitDirection.x * 300.f, -450.f });

	}

	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void GoombaDeadState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void GoombaDeadState::Update(float deltaTime)
{
	if (isJumpDie)
		IsJumpDie(deltaTime);
	else
		IsHitDie(deltaTime);

}

void GoombaDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void GoombaDeadState::LateUpdate(float deltaTime)
{
}