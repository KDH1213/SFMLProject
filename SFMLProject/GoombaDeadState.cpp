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
}

void GoombaDeadState::Exit()
{
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