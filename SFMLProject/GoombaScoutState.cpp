#include "stdafx.h"
#include "GoombaScoutState.h"

GoombaScoutState::GoombaScoutState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
{
}

GoombaScoutState::~GoombaScoutState()
{
}

void GoombaScoutState::Awake()
{
}

void GoombaScoutState::Start()
{
}

void GoombaScoutState::Enter()
{
}

void GoombaScoutState::Exit()
{
}

void GoombaScoutState::Update(float deltaTime)
{
}

void GoombaScoutState::FixedUpdate(float fixedDeltaTime)
{
}

void GoombaScoutState::LateUpdate(float deltaTime)
{
}
