#include "stdafx.h"
#include "Player.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, fsm(this)
	, isJump(false)
	, currentStatus(2, 500.f, 200.f, 350.f)
	, isFlipX(false)
	, hitTime(2.f)
	, currentHitTime(0.f)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateAnimator();
	animator->LoadCsv("animators/mario.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	defaultColor = sprite.getColor();
	effectColor = defaultColor;
	effectColor.a = 120;
}

Player::~Player()
{
}

void Player::Awake()
{
}

void Player::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();

	fsm.Start();
	fsm.ChangeState(PlayerStateType::Idle);
}

void Player::InputMove()
{
	
}

void Player::InputJump()
{
}

void Player::TakeDamage()
{
	if (isHit)
		return;

	--currentStatus.hp;
	isHit = true;

	if (currentStatus.hp == 0)
	{
		fsm.ChangeState(PlayerStateType::Dead);
		return;
	}
	else
	{
		fsm.ChangeState(PlayerStateType::Hit);
		sprite.setColor(effectColor);
	}

	currentHitTime = hitTime;
}

void Player::OnFlipX()
{
	isFlipX = !isFlipX;

	scale.x *= -1.f;
	SetScale(scale);
}


void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);

	if (isHit)
	{
		currentHitTime -= deltaTime;

		if (currentHitTime <= 0.f)
		{
			sprite.setColor(defaultColor);
			isHit = false;
			currentHitTime = 0.f;
		}
	}
}

void Player::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime); 

	/*if (!isHit)
	{
		if (position.y >= 0.f)
		{
			isJump = false;
			position.y = 0.f;

			rigidBody->SetGround(true);
			SetPosition(position);
		}
	}*/
	
}

void Player::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Player::Render(sf::RenderWindow& renderWindow)
{
	animator->Render(renderWindow);
	collider->Render(renderWindow);
}
void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
	collider->SetPosition(pos);
}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;

	animator->SetScale(scale);
	collider->SetOwnerScale(scale);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	sprite.rotate(angle);
	collider->SetRotation(angle);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);	
	collider->SetOrigin(newOrigin);
}

void Player::CreateAnimator()
{
	if (animator != nullptr)
		return;

	animator = new Animator(this, sprite);
}

sf::FloatRect Player::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

PlayerSaveData Player::GetPlayerSaveData() const
{
	return PlayerSaveData({this->GetGameObjectSaveData(), currentStatus});
}

void Player::LoadData(const PlayerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	currentStatus = data.status;
}
