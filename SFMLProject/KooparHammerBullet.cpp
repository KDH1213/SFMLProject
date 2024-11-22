#include "stdafx.h"
#include "KooparHammerBullet.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Rigidbody.h"

KooparHammerBullet::KooparHammerBullet(const std::string& texId, const std::string& name)
	: Bullet(ColliderLayer::EnemyBullet, texId, name)
	, isFiring(true)
{
	CreateAnimator();
	animator->LoadCsv("animators/koopaHammer.csv");

	rigidBody = new Rigidbody(this);
}

void KooparHammerBullet::OnFiring()
{
	rigidBody->SetGround(false);
	speed = Utils::RandomRange(500.f, 700.f);
	rigidBody->SetVelocity({ speed, -400.f });
	isFiring = true;

	animator->ChangeAnimation("koopaHammer", true);
}

void KooparHammerBullet::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("koopaHammer", true);
	animator->SetPlaying(false);

}

void KooparHammerBullet::Update(const float& deltaTime)
{
	if (animator != nullptr)
		animator->Update(deltaTime);

	if (isFiring)
	{
		if (position.y > 2000.f)
			OnDestory();
	}
}

void KooparHammerBullet::FixedUpdate(const float& deltaTime)
{
	rigidBody->SetVelocity({ speed * moveDirection.x, rigidBody->GetCurrentVelocity().y });
	rigidBody->FixedUpdate(deltaTime * 0.5f);
}

void KooparHammerBullet::OnCollisionEnter(Collider* target)
{
}

void KooparHammerBullet::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}
