#include "stdafx.h"
#include "GameClearObject.h"
#include "Collider.h"
#include "GameManager.h"
#include "Rigidbody.h"
#include "Player.h"

GameClearObject::GameClearObject(const std::string& name)
	: GameObject(name)
	, player(nullptr)
	, currentTime(0.f)
	, moveTime(1.f)
	, isStartClearEvent(false)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::SavePoint);
}

void GameClearObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void GameClearObject::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void GameClearObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void GameClearObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void GameClearObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void GameClearObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void GameClearObject::Update(const float& deltaTime)
{
	if (!isStartClearEvent)
		return;

	currentTime += deltaTime;
	Utils::Lerp(player->GetPosition().y, destinationPosition.y, currentTime);

	if (currentTime >= 1.f)
	{
		currentTime = 1.f;
		isStartClearEvent = false;
	}
}

void GameClearObject::Render(sf::RenderWindow& renderWindow)
{
	collider->Render(renderWindow);
}

void GameClearObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		InputManager::GetInstance().SetInputable(false);
		player = (Player*)target->GetOwner();
		player->GetRigidbody()->Disable();

		startPosition = player->GetPosition();
		currentTime = startPosition.y / destinationPosition.y - maxStartPosition.y;
	}
}

sf::FloatRect GameClearObject::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect GameClearObject::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

SavePointSaveData GameClearObject::GetSavePointSaveData() const
{
	return SavePointSaveData({ GetGameObjectSaveData(), destinationPosition });
}

void GameClearObject::LoadSavePointSaveData(const SavePointSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	/// restartPosition = data.restartPosition;
}