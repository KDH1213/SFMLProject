#include "stdafx.h"
#include "StartButton.h"
#include "Scene.h"

StartButton::StartButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UIButtonObject(textId, name, textSize, textColor)
{
}

void StartButton::OnCollisionEnter(Collider* target)
{
	textColor = sf::Color::Red;
	text.setFillColor(textColor);
}

void StartButton::OnCollisionStay(Collider* target)
{
	if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Left))
	{
		for (auto& buttonEvent : buttonEvents)
		{
			if(buttonEvent)
				buttonEvent();
		}
	}
}

void StartButton::OnCollisionEnd(Collider* target)
{
	textColor = sf::Color::White;
	text.setFillColor(textColor);
}
