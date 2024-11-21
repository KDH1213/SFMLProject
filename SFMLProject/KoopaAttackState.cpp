#include "stdafx.h"
#include "KoopaAttackState.h"
#include "Rigidbody.h"
#include "Animation.h"
#include "Animator.h"
#include "FireBullet.h"

KoopaAttackState::KoopaAttackState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Attack)
	, rigidbody(nullptr)
{
}

KoopaAttackState::~KoopaAttackState()
{
}


void KoopaAttackState::StartAttack()
{
	FireBullet* bullet = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new FireBullet(), LayerType::EnemyBullet);

	sf::Vector2f direciton;

	if (enemy->IsFlipX())
	{
		direciton = sf::Vector2f::left;
		bullet->SetPosition(enemy->GetPosition() + sf::Vector2f::left * 3.f);
		bullet->GetRigidbody()->SetVelocity({ -500.f, 0.f });
	}
	else
	{
		direciton = sf::Vector2f::right;
		bullet->SetPosition(enemy->GetPosition() + sf::Vector2f::right * 3.f);
		bullet->GetRigidbody()->SetVelocity({ 500.f, 0.f });
	}

	direciton.Normalized();

	bullet->SetMoveDirection(direciton);

	bullet->Awake();
	bullet->Start();
}

void KoopaAttackState::EndAttack()
{
	fsm->ChangeState(EnemyStateType::Idle);
}

void KoopaAttackState::Awake()
{
}

void KoopaAttackState::Start()
{
}

void KoopaAttackState::Enter()
{
	enemy->GetAnimator()->ChangeAnimation("koopaAttack", true);

	Animation* animation = enemy->GetAnimator()->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&KoopaAttackState::StartAttack, this), 0);
	animation->SetAnimationEndEvent(std::bind(&KoopaAttackState::EndAttack, this), 1);
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void KoopaAttackState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}

	Animation* animation = enemy->GetAnimator()->GetCurrentAnimation();
	animation->ClearEndEvent(0);
	animation->ClearEndEvent(1);
}

void KoopaAttackState::Update(float deltaTime)
{
}

void KoopaAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaAttackState::LateUpdate(float deltaTime)
{
}