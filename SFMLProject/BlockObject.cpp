#include "stdafx.h"
#include "BlockObject.h"
#include "Collider.h"


BlockObject::BlockObject(BlockType type, const std::string& texId, const std::string& name)
    : GameObject(name)
    , type(type)
	, textureID(texId)
{
}

void BlockObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	render.setTextureRect(textureUvRect);

	SetOrigin(originPreset);
	if (collider != nullptr)
		collider->Reset();
}

void BlockObject::SetUvRect(const sf::IntRect uvRect)
{
}

void BlockObject::SetScale(const sf::Vector2f& scale)
{
}

sf::Vector2f BlockObject::GetScale() const
{
	return sf::Vector2f();
}

void BlockObject::SetRotation(float angle)
{
}

void BlockObject::SetPosition(const sf::Vector2f& pos)
{
}

void BlockObject::SetOrigin(Origins preset)
{
}

void BlockObject::SetOrigin(const sf::Vector2f& newOrigin)
{
}

void BlockObject::OnCollisionEnter(Collider* target)
{
}

void BlockObject::OnCollisionStay(Collider* target)
{
}

void BlockObject::OnCollisionEnd(Collider* target)
{
}

void BlockObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(render);
}

bool BlockObject::Save() const
{
    return false;
}

bool BlockObject::Load()
{
    return false;
}

bool BlockObject::SaveCsv(const std::string& filePath) const
{
    return false;
}

bool BlockObject::LoadCsv(const std::string& filePath)
{
    return false;
}
