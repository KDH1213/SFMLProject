#include "stdafx.h"
#include "PlayerUpgradeState.h"

#include "Animation.h"
#include "Animator.h"
#include "Collider.h"

PlayerUpgradeState::PlayerUpgradeState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
{
	animationKeys.push_back("marioUpgrade");
	animationKeys.push_back("marioFireUpgrade");
}

PlayerUpgradeState::~PlayerUpgradeState()
{
}

void PlayerUpgradeState::StartEffect()
{
	if (player->GetCurrentHP() == 1)
	{
		sf::Vector2f currentOrigin = player->GetOrigin();
		player->SetOrigin(Origins::TopCenter);
		currentOrigin = player->GetOrigin();
		currentOrigin.y = currentOrigin.y * 0.5f;

		player->GetAnimator()->ChangeAnimation(animationKeys[0], true, true);
		

		changePosition = player->GetPosition();
		changePosition.y -= 48.f;


		Animation* animation = player->GetAnimator()->GetCurrentAnimation();

		animation->SetAnimationStartEvent(std::bind(&PlayerUpgradeState::ChangePosition, this), 1);
		animation->SetAnimationEndEvent(std::bind(&PlayerUpgradeState::OnAnimationEnd, this), 2);
		// changePosition.y += (animation->GetFrameInfo()[0].rectSize.y - animation->GetFrameInfo()[2].rectSize.y) * 0.5f;
	}
	/*else if(player->GetCurrentHP() == 2)
	{
		player->GetAnimator()->ChangeAnimation(animationKeys[1], true, true);
	}*/

}

void PlayerUpgradeState::ChangePosition()
{
	player->SetPosition(changePosition);
	player->GetCollider()->SetScale(player->GetCollider()->GetScale() * 2.f);
}

void PlayerUpgradeState::OnAnimationEnd()
{
	fsm->ChangeState(PlayerStateType::Idle);
}

void PlayerUpgradeState::Awake()
{
}

void PlayerUpgradeState::Start()
{
}

void PlayerUpgradeState::Enter()
{
	PlayerBaseState::Enter();

	currentTime = 0.f;

	StartEffect();

	player->SetOrigin(Origins::MiddleCenter);
	player->GetCollider()->SetActive(false);
	TimeManager::GetInstance().SetTimeScale(0.f);
}

void PlayerUpgradeState::Exit()
{
	PlayerBaseState::Exit();
	TimeManager::GetInstance().SetTimeScale(1.f);
	player->GetCollider()->SetActive(true);
	player->SetPosition(changePosition);

	if (player->GetCurrentHP() == 1)
	{
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->ClearStartEvent(1);
		animation->ClearEndEvent(2);

	}
	player->AddHp();
}

void PlayerUpgradeState::Update(float deltaTime)
{
}

void PlayerUpgradeState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerUpgradeState::LateUpdate(float deltaTime)
{
}