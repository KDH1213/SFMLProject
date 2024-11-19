#include "stdafx.h"
#include "CoinObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

CoinObject::CoinObject()
	: ItemObject(ItemType::Coin, "Items", "Coin")
{
	CreateAnimator();

	animator->LoadCsv("animators/coin.csv");
}

void CoinObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("coinIdle", true);
}

void CoinObject::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
}

void CoinObject::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}
