#pragma once

#include "SpriteGameObject.h"

class LabberObject : public SpriteGameObject
{
private:
	sf::IntRect textureRect;

public:
	void Start() override;
	void SetScale(const sf::Vector2f& scale) override;
	void OnCollisionEnter(Collider* target) override;
public:
	LabberObject(const sf::IntRect& textureRect, const std::string& texId, const std::string& name = "");
	virtual ~LabberObject() = default;
};

