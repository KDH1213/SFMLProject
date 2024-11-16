#include "stdafx.h"
#include "GoombaIdleState.h"

GoombaIdleState::GoombaIdleState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Idle)
{
}

GoombaIdleState::~GoombaIdleState()
{
}

void GoombaIdleState::Awake()
{
}

void GoombaIdleState::Start()
{
}

void GoombaIdleState::Enter()
{
}

void GoombaIdleState::Exit()
{
}

void GoombaIdleState::Update(float deltaTime)
{
}

void GoombaIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void GoombaIdleState::LateUpdate(float deltaTime)
{
}