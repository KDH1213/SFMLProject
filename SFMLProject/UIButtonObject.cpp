#include "stdafx.h"
#include "UIButtonObject.h"
#include "Collider.h"

UIButtonObject::UIButtonObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UITextGameObject(textId, name, textSize, textColor)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::UI);
}

void UIButtonObject::Start()
{
	text.setFont(ResourcesManager<sf::Font>::GetInstance().Get(textId));
	SetOrigin(originPreset);

	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
}

void UIButtonObject::SetButtonSize(const sf::Vector2f& size)
{
}

void UIButtonObject::SetColliderSize(const sf::Vector2f& size)
{
	collider->SetOwnerScale(size);
	collider->SetOrigin(originPreset);
}

void UIButtonObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(text, preset);
	collider->SetOrigin(preset);
}

void UIButtonObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void UIButtonObject::SetPosition(const sf::Vector2f& pos)
{
	UIGameObject::SetPosition(pos);
	text.setPosition(pos);
	collider->SetPosition(pos);
}

void UIButtonObject::OnCollisionEnter(Collider* target)
{
}

void UIButtonObject::OnCollisionStay(Collider* target)
{
}
