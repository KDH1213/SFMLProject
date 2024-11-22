#pragma once

#include "EnemyBaseState.h"

class KoopaDeadState : public EnemyBaseState
{
private:
	Rigidbody*	rigidbody;

	float		rotationTime;
	float		currentRotationTime;


	float		currentTime;
	bool		isStartEvent;
	bool		isLabberDie;
	bool		isHitDie;
	bool		isEndRotation;


private:
	void EndDead();
	void LabberDie();
	void HitDie(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	KoopaDeadState(EnemyFSM* fsm);
	~KoopaDeadState();
};

