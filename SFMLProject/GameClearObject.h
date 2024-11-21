
#pragma once
#include "GameObject.h"
#include "GameObjectSaveData.h"

class Player;

class GameClearObject : public GameObject
{
protected:
	sf::RectangleShape	render;
	Player*				player;

	sf::Vector2f		maxStartPosition;
	sf::Vector2f		startPosition;
	sf::Vector2f		destinationPosition;

	float				currentTime;
	float				moveTime;
	bool				isStartClearEvent;

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	
	void SetMaxStartPosition(const sf::Vector2f& pos) { maxStartPosition = pos; }
	void SetDestinationPosition(const sf::Vector2f& pos) { destinationPosition = pos; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void Start() override;

	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	SavePointSaveData GetSavePointSaveData() const;
	void LoadSavePointSaveData(const SavePointSaveData& data);

public:
	GameClearObject(const std::string& name = "GameClearPoint");
	virtual ~GameClearObject() = default;
	GameClearObject& operator= (const GameClearObject& other) = delete;
};

