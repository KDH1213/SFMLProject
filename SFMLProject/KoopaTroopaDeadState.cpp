#include "stdafx.h"
#include "KoopaTroopaDeadState.h"


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
}

void KoopaTroopaDeadState::Enter()
{
	enemy->SetCurrentState(stateType);
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