#include "stdafx.h"
#include "KoopaTroopaDeadState.h"

#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"

KoopaTroopaDeadState::KoopaTroopaDeadState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
{
}

KoopaTroopaDeadState::~KoopaTroopaDeadState()
{
}

void KoopaTroopaDeadState::Awake()
{
}

void KoopaTroopaDeadState::Start()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaTroopaDeadState::Enter()
{
	enemy->SetCurrentState(stateType);

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
}

void KoopaTroopaDeadState::Exit()
{
}

void KoopaTroopaDeadState::Update(float deltaTime)
{
}

void KoopaTroopaDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaTroopaDeadState::LateUpdate(float deltaTime)
{
}