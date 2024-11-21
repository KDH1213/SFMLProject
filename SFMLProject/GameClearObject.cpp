#include "stdafx.h"
#include "GameClearObject.h"
#include "Collider.h"
#include "GameManager.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerFSM.h"
#include "Animation.h"

GameClearObject::GameClearObject(const std::string& name)
	: GameObject(name)
	, player(nullptr)
	, currentTime(0.f)
	, moveTime(1.f)
	, isStartClearEvent(false)
	, currentEventIndex(0)
	, isStartFlip(false)
	, isStartMove(false)
	, endMoveTime(3.f)
	, currentEndMoveTime(0.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::CleraPoint);

	gameClearEvents.push_back(std::bind(&GameClearObject::StartMove, this));
	gameClearEvents.push_back(std::bind(&GameClearObject::FlipEvent, this));
	gameClearEvents.push_back(std::bind(&GameClearObject::Move, this));
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

void GameClearObject::StartMove()
{
	sf::Vector2f currentPos = player->GetPosition();
	currentPos.y = Utils::Lerp(startPosition.y, destinationPosition.y, currentTime);

	if (currentTime >= 1.f)
	{
		player->GetAnimator()->GetCurrentAnimation()->Stop();
		currentTime = 1.f;
		// isStartClearEvent = false;
		++currentEventIndex;
	}
	player->SetPosition(currentPos);
}

void GameClearObject::FlipEvent()
{
	if (!isStartFlip)
	{
		sf::Vector2f currentPos = player->GetPosition();
		currentPos.x += player->GetCollider()->GetScale().x + 10.f;
		player->SetPosition(currentPos);
		player->OnFlipX();
		isStartFlip = true;
		currentTime = 0.f;
	}
	else
	{
		if (currentTime > 0.5f)
		{
			++currentEventIndex;
		}
	}
	
}

void GameClearObject::Move()
{
	if (!isStartMove)
	{
		player->GetRigidbody()->ResetVelocity();
		player->GetRigidbody()->SetActive(true);
		player->GetRigidbody()->SetGround(false);
		player->GetCollider()->SetActive(true);
		player->GetAnimator()->ChangeAnimation("marioRun", true);
		player->OnFlipX();
		isStartMove = true;
		currentEndMoveTime = 0.f;
	}
	else
	{
		sf::Vector2f currentPos = player->GetPosition();
		currentPos.x = Utils::Lerp(startPosition.x, endMovePosition.x, currentEndMoveTime / endMoveTime);
		player->SetPosition(currentPos);

		if (currentEndMoveTime >= endMoveTime)
		{
			isStartClearEvent = false;
			player->SetActive(false);
		}
	}
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

	if (isStartMove)
		currentEndMoveTime += deltaTime;

	gameClearEvents[currentEventIndex]();
}

void GameClearObject::Render(sf::RenderWindow& renderWindow)
{
	collider->Render(renderWindow);
}

void GameClearObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		InputManager::GetInstance().SetInputable(true);
		player = (Player*)target->GetOwner();
		player->GetRigidbody()->Disable();

		startPosition = player->GetPosition();
		currentTime = startPosition.y / (destinationPosition.y - maxStartPosition.y);
		isStartClearEvent = true;
		collider->SetActive(false);
		player->GetFSM().ChangeState(PlayerStateType::GameClear);
		// player->GetAnimator()->ChangeAnimation("")
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

GameClearSaveData GameClearObject::GetGameClearSaveData() const
{
	return GameClearSaveData({ GetGameObjectSaveData(), maxStartPosition, destinationPosition, endMovePosition, endMoveTime, moveTime });
}

void GameClearObject::LoadGameClearSaveData(const GameClearSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	maxStartPosition = data.maxStartPosition;
	destinationPosition = data.destinationPosition;
	endMovePosition = data.endMovePosition;
	endMoveTime = data.endMoveTime;
	moveTime = data.moveTime;
}
