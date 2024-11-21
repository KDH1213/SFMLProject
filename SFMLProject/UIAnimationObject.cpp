#include "stdafx.h"
#include "UIAnimationObject.h"

void UIAnimationObject::Awake()
{
}

void UIAnimationObject::SetPosition(const sf::Vector2f& pos)
{
}

void UIAnimationObject::Render(sf::RenderWindow& renderWindow)
{
}

void UIAnimationObject::Start()
{
}

void UIAnimationObject::Update(const float& deltaTime)
{
}

void UIAnimationObject::FixedUpdate(const float& deltaTime)
{
}

void UIAnimationObject::LateUpdate(const float& deltaTime)
{
}

void UIAnimationObject::SetOrigin(Origins preset)
{
}

void UIAnimationObject::SetOrigin(const sf::Vector2f& newOrigin)
{
}

UIAnimationObject::UIAnimationObject(const std::string& name)
	: UIGameObject(name)
{
}
