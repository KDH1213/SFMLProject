#include "stdafx.h"
#include "LabberObject.h"
#include "Collider.h"
#include "Koopa.h"
#include "Enemy.h"

LabberObject::LabberObject(const sf::IntRect& textureRect, const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, textureRect(textureRect)
{
	scale = sf::Vector2f(4.f, 4.f);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);
}


void LabberObject::Start()
{
	sprite.setTextureRect(textureRect);
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
}

void LabberObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
	collider->SetScale({ textureRect.width * scale.x, textureRect.height * scale.y });
}

void LabberObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		auto& objects = SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Enemy);

		for (auto& object : objects)
		{
			Koopa* koopa = dynamic_cast<Koopa*>(object);
			if (koopa != nullptr)
			{
				koopa->OnDead();
			}
		}

		OnDestory();
	}
} 
