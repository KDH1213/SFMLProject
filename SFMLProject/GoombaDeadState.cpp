#include "stdafx.h"
#include "GoombaDeadState.h"

GoombaDeadState::GoombaDeadState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
{
}

GoombaDeadState::~GoombaDeadState()
{
}

void GoombaDeadState::Awake()
{
}

void GoombaDeadState::Start()
{
}

void GoombaDeadState::Enter()
{
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
}

void GoombaDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void GoombaDeadState::LateUpdate(float deltaTime)
{
}