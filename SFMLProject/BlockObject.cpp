#include "stdafx.h"
#include "BlockObject.h"


BlockObject::BlockObject(BlockType type, const std::string& texId, const std::string& name)
    : SpriteGameObject(texId, name)
    , type(type)
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
