#include "stdafx.h"
#include "KoopaDeadState.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"

KoopaDeadState::KoopaDeadState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
	, isStartEvent(false)
	, currentTime(0.f)
	, rigidbody(nullptr)
	, isLabberDie(false)
	, isHitDie(false)
	, rotationTime(0.5f)
	, currentRotationTime(0.f)
	, isEndRotation(false)
{
}

KoopaDeadState::~KoopaDeadState()
{
}


void KoopaDeadState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaDeadState::Start()
{
}

void KoopaDeadState::Enter()
{
	rigidbody->ResetVelocity();
	rigidbody->SetGround(false);
	enemy->GetCollider()->SetActive(false);

	if (enemy->GetHP() == 0)
	{
		isHitDie = true;
		currentRotationTime = 0.f;
		rigidbody->SetVelocity({ 0.f, -800.f });
	}
	else
	{
		TimeManager::GetInstance().SetTimeScale(0.f);
		enemy->GetAnimator()->ChangeAnimation("koopaIdle", true, true);
		InputManager::GetInstance().SetInputable(true);
		currentTime = 0.f;
		isLabberDie = true;
	}
}

void KoopaDeadState::Exit()
{
}

void KoopaDeadState::Update(float deltaTime)
{
	if (isLabberDie)
		LabberDie();
	else
		HitDie(deltaTime);

	if (enemy->GetPosition().y > 2000.f)
	{
		EndDead();
		enemy->OnDestory();
	}
}

void KoopaDeadState::FixedUpdate(float fixedDeltaTime)
{
	if(isStartEvent)
		rigidbody->FixedUpdate(TimeManager::GetInstance().GetUnScaleFixedDeletaTime() * 0.5f);
}

void KoopaDeadState::LateUpdate(float deltaTime)
{
}
void KoopaDeadState::EndDead()
{
	TimeManager::GetInstance().SetTimeScale(1.f);
	InputManager::GetInstance().SetInputable(false);
}

void KoopaDeadState::LabberDie()
{
	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (!isStartEvent && currentTime > 0.5f)
	{
		isStartEvent = true;
	}
}

void KoopaDeadState::HitDie(float deltaTime)
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
		}
	}
}
