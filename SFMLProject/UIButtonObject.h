#pragma once
#include "UITextGameObject.h"
class UIButtonObject : public UITextGameObject
{
protected:
	sf::Vector2f colliderSize;
	sf::Vector2f buttonSize;

public:
	void SetButtonSize(const sf::Vector2f& size);
	void SetColliderSize(const sf::Vector2f& size);

public:
	void Start() override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;

public:
	UIButtonObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~UIButtonObject() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	UIButtonObject& operator= (const UIButtonObject& other) = delete;
};

