#include "stdafx.h"
#include "Goomba.h"

#include "Animator.h"
#include "Collider.h"

Goomba::Goomba(const std::string& name)
	: Enemy(name)
{
	fsm = new GoombaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/mario.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

Goomba::~Goomba()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void Goomba::Awake()
{
	animator->ChangeAnimation("marioIdle", true);
}

void Goomba::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Idle);
}
