#pragma once
#include "UIButtonObject.h"
class StartButton : public UIButtonObject
{
public:
	void SetButtonEvent(std::function<void()> buttonEvent) { buttonEvents.push_back(buttonEvent); }

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	StartButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~StartButton() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	StartButton& operator= (const StartButton& other) = delete;
};

