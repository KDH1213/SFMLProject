#include "stdafx.h"
#include "CoinObject.h"

CoinObject::CoinObject()
	: ItemObject(ItemType::Coin, "Items", "Coin")
{
	textureUVRect = { 0,6 *16,16,16 };
}

//void CoinObject::Start()
//{
//}
