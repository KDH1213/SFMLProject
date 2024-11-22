#pragma once
#include "Enemy.h"

class Player;
class KooparHammerBullet;

class Koopa : public Enemy
{
private:
	std::vector<KooparHammerBullet*>	hammers;
	Player*								player;
	sf::Vector2f						hammerPosition;

	float								currentJumpTime;
	float								jumpTime;
	bool								isJump;
	bool								isDead;
	bool								isLabberDead;

	int									currentHammerIndex;
	int									createHammerCount;
	float								currentHammerFiringTime;
	float								hammerFiringTime;
	bool								isCreateHammer;
	bool								isEndHammerFiring;

public:
	void OnJump();
	void OnDead();
	void OnCreateHammer();
	void HammerFiring(const float& deltaTime);

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

