#pragma once

#include "PlayerBaseState.h"
class PlayerUpgradeState : public PlayerBaseState
{
private:
	sf::Vector2f changePosition;
	sf::Vector2f originalPosition;
	float	currentTime;

private:
	void StartEffect();
	void ChangePosition();
	void OnAnimationEnd();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	PlayerUpgradeState(PlayerFSM* fsm);
	~PlayerUpgradeState();
};

