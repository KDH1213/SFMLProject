#include "stdafx.h"
#include "StarObject.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

StarObject::StarObject()
	: ItemObject(ItemType::Star, "Items", "Star")
	, moveSpeed(500.f)
	, moveDirection(sf::Vector2f::right)
{
	rigidBody = new Rigidbody(this);

	CreateAnimator();
	animator->LoadCsv("animators/star.csv");
}

void StarObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("star", true);
}

void StarObject::Update(const float& deltaTime)
{
	animator->Update(deltaTime);

	if (isCreateEvent)
	{
		position += sf::Vector2f::up * speed * deltaTime;
		if (position.y <= createEndPosition.y)
		{
			isCreateEvent = false;
			position.y = createEndPosition.y;
		}

		SetPosition(position);
	}
}
void StarObject::FixedUpdate(const float& deltaTime)
{
}

void StarObject::OnCollisionEnter(Collider* target)
{
}

void StarObject::OnCollisionStay(Collider* target)
{
}

void StarObject::OnCollisionEnd(Collider* target)
{
}

void StarObject::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}
