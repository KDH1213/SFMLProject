#include "stdafx.h"
#include "PlayerDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
{
}

PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::Awake()
{
}

void PlayerDeadState::Start()
{
}

void PlayerDeadState::Enter()
{
	PlayerBaseState::Enter();
	player->GetAnimator()->ChangeAnimation("marioHit", true, true);
}

void PlayerDeadState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDeadState::Update(float deltaTime)
{
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerDeadState::LateUpdate(float deltaTime)
{
}