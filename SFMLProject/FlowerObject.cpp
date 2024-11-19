#include "stdafx.h"
#include "FlowerObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

FlowerObject::FlowerObject()
	: ItemObject(ItemType::Flower, "Items", "Flower")
{
	CreateAnimator();
	//animator->LoadCsv("animators/flower.csv");
}

void FlowerObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	//animator->Start();
	collider->Reset();
	//collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	// animator->ChangeAnimation("FlowerIdle", true);
}
