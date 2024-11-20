#pragma once
#include "UIButtonObject.h"
class StartButton : public UIButtonObject
{
public:
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;

public:
	StartButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~StartButton() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	StartButton& operator= (const StartButton& other) = delete;
};

