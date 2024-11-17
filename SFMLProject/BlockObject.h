#pragma once

#include "SpriteGameObject.h"

class Player;

class BlockObject : public GameObject
{
protected:
	sf::RectangleShape	render;
	BlockType			type;
	Player*				player;

	sf::IntRect			textureUvRect;
	sf::Vector2u		rectSize;
	std::string			textureID;

public:
	void Start() override;

	virtual void SetUvRect(const sf::IntRect uvRect);
	void SetScale(const sf::Vector2f& scale) override;
	sf::Vector2f GetScale() const override;

	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void Render(sf::RenderWindow& renderWindow) override;
public:
	virtual void OnCollisionEnter(Collider* target);
	virtual void OnCollisionStay(Collider* target);
	virtual void OnCollisionEnd(Collider* target);

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	BlockObject(BlockType type, const std::string& texId, const std::string& name = "Block");
	virtual ~BlockObject() = default;
	BlockObject& operator= (const BlockObject& other) = delete;
};

