#include "stdafx.h"
#include "GoombaScoutState.h"
#include "Rigidbody.h"

GoombaScoutState::GoombaScoutState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
{
}

GoombaScoutState::~GoombaScoutState()
{
}

void GoombaScoutState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void GoombaScoutState::Start()
{
}

void GoombaScoutState::Enter()
{
	moveDirection = enemy->GetMoveDirection() * -1.f;
	enemy->SetMoveDirection(moveDirection);
	speed = enemy->GetSpeed();
	rigidbody->SetVelocity({ moveDirection.x * speed , rigidbody->GetCurrentVelocity().y });


	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void GoombaScoutState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}

	rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
}

void GoombaScoutState::FixedUpdate(float fixedDeltaTime)
{
}
