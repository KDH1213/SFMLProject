#include "stdafx.h"
#include "TileMapController.h"
#include "TileMap.h"
#include "Scene.h"

TileMapController::TileMapController(const std::string& name)
    : GameObject(name)
    , textureTileSize({16, 16})
    , cellCount(30,20)
    , cellSize(64.f,64.f)
    , spriteSheetId("tiles")
{
}

TileMapController::~TileMapController()
{
}


void TileMapController::SetCellCount(const sf::Vector2u& tileCount)
{
    this->cellCount = tileCount;
}

void TileMapController::SetCellSize(const sf::Vector2f& cellSize)
{
    this->cellSize = cellSize;
}

void TileMapController::SetTileTextrueRectSize(const sf::Vector2u& texTileSize)
{
    textureTileSize = texTileSize;
}

void TileMapController::AddTileMap(int count)
{
    for (int i = 0; i < count; ++i)
    {
        TileMap* tile = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new TileMap(spriteSheetId, "Map"), LayerType::TileMap);
        if (tileMaps.empty())
        {
            tile->SetPosition(position);
        }
        else
        {
            auto bouns = tileMaps.back()->GetGlobalBounds();
            tile->SetPosition(sf::Vector2f(tileMaps.back()->GetPosition().x + bouns.getSize().x, position.y));
        }
        tile->SetTileInfo(spriteSheetId, cellCount, cellSize, textureTileSize);
        tileMaps.push_back(tile);
    }
}

bool TileMapController::SaveCsv(const std::string& filePath) const
{
    int count = 1;

    for (auto& tileMap : tileMaps)
    {
        tileMap->SaveCsv("tileMap/" + tileMap->GetName() + std::to_string(count++) + ".csv");
    }

    return false;
}

bool TileMapController::LoadCsv(const std::string& filePath)
{
    return false;
}

sf::FloatRect TileMapController::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect TileMapController::GetGlobalBounds() const
{
    return sf::FloatRect();
}
