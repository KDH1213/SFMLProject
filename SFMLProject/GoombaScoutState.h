#pragma once
#include "EnemyBaseState.h"
class GoombaScoutState : public EnemyBaseState
{
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	GoombaScoutState(EnemyFSM* fsm);
	~GoombaScoutState();
};

