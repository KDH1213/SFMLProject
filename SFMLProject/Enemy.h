#pragma once

#include "GameObject.h"
#include "EnemyFSM.h"

class Enemy : public GameObject
{
protected:
	sf::Sprite		sprite;

	EnemyFSM*		fsm;
	sf::Vector2f	moveDirection;
	DefaultStatus	currentStatus;
	EnemyStateType	currentState;

	bool			isDead;
	bool			isFlipX;

public:
	void TakeDamage();
	void OnFlipX();
	bool IsFlipX() { return isFlipX; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	const sf::Vector2f& GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(const sf::Vector2f& direction) { moveDirection = direction; }
public:
	void CreateAnimator() override;
	float GetSpeed() { return currentStatus.speed; }


public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;


	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	Enemy(const std::string& name = "Enemy");
	virtual ~Enemy();
	Enemy& operator= (const Enemy& other) = delete;
};

