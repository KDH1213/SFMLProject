#include "stdafx.h"
#include "PlayerDownState.h"
#include "Animator.h"
#include "Rigidbody.h"

PlayerDownState::PlayerDownState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Down)
{
	animationKeys.push_back("marioSmallIdle");
	animationKeys.push_back("marioIdle");
	animationKeys.push_back("marioFireIdle");
}

PlayerDownState::~PlayerDownState()
{
}

void PlayerDownState::Awake()
{
}

void PlayerDownState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerDownState::Enter()
{
	PlayerBaseState::Enter();

	animationKeyIndex = player->GetCurrentHP() - 1;
	player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);
}

void PlayerDownState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDownState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetAxis(Axis::Horizontal) != 0.f)
		fsm->ChangeState(PlayerStateType::Run);

	if ((InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)))
	{
		if (rigidbody->IsGround())
			fsm->ChangeState(PlayerStateType::Jump);
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z))
	{
		player->Attack();
	}
}

void PlayerDownState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerDownState::LateUpdate(float deltaTime)
{
}
