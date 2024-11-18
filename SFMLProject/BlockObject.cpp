#include "stdafx.h"
#include "BlockObject.h"
#include "Collider.h"


BlockObject::BlockObject(BlockType type, const std::string& texId, const std::string& name)
    : GameObject(name)
    , type(type)
	, textureID(texId)
	, player(nullptr)
	, textureUVRect(0,0,16,16)
	, rectSize(32.f,32.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Block);
}

void BlockObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	render.setTextureRect(textureUVRect);

	SetOrigin(originPreset);
	collider->Reset();
}

void BlockObject::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	render.setTextureRect(uvRect);
	//rectSize = 
}

void BlockObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(rectSize * scale);
	collider->SetScale(rectSize * scale);
	SetOrigin(originPreset);
}

sf::Vector2f BlockObject::GetScale() const
{
	return scale;
}

void BlockObject::SetSize(const sf::Vector2f& size)
{
	rectSize = size;
	render.setSize(rectSize);
}

void BlockObject::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void BlockObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void BlockObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void BlockObject::SetOrigin(const sf::Vector2f & newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
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

sf::FloatRect BlockObject::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect BlockObject::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

void BlockObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(render);
	collider->Render(renderWindow);
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
