#pragma once

#include "UIGameObject.h"

class UIAnimationObject : public UIGameObject
{
protected:
	sf::Sprite		sprite;
public:
	void Awake() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	UIAnimationObject(const std::string& name);
	virtual ~UIAnimationObject() = default;
	UIAnimationObject& operator= (const UIAnimationObject& other) = delete;
};

