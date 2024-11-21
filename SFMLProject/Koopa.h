#pragma once
#include "Enemy.h"

class Player;

class Koopa : public Enemy
{
private:
	Player* player;

	float	currentJumpTime;
	float	jumpTime;
	bool	isJump;

public:
	void OnJump();

public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);
public:
	Koopa(const std::string& name = "Koopa");
	virtual ~Koopa();
};

