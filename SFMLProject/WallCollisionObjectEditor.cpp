#include "stdafx.h"
#include "WallCollisionObjectEditor.h"
#include "imgui.h"
#include "WallCollisionObject.h"

WallCollisionObjectEditor::WallCollisionObjectEditor()
	: GUI("WallCollisionObjectEditor")
	, isStartInput(false)
	, isEndInput(false)
	, isCreateObject(false)
{
}

WallCollisionObjectEditor::~WallCollisionObjectEditor()
{
}
void WallCollisionObjectEditor::Init()
{
}

void WallCollisionObjectEditor::Update()
{
	ImGui::Begin("##WallCollisionObjectEditor");
	ImGui::SeparatorText("WallCollisionObjectEditor");


	float cellSizeArr[2] = { cellSize.x, cellSize.y };
	ImGui::Text("CellSize"); ImGui::SameLine();
	if (ImGui::InputFloat2("##CellSize", cellSizeArr))
	{
		if (cellSizeArr[0] > 0.f)
			cellSize.x = cellSizeArr[0];
		if(cellSizeArr[0] > 0.f)
			cellSize.y = cellSizeArr[1];
	}

	if (isCreateObject && InputManager::GetInstance().GetKeyUp(sf::Mouse::Left) && !(isStartInput && isEndInput))
	{
		sf::Vector2f currentPos = SceneManager::GetInstance().GetCurrentScene()->IsFreeView() ? SceneManager::GetInstance().GetCurrentScene()->ScreenToFreeViewWorld(InputManager::GetInstance().GetMousePosition()) : SceneManager::GetInstance().GetCurrentScene()->ScreenToWorld(InputManager::GetInstance().GetMousePosition());
		int posX = (int)(currentPos.x / cellSize.x);
		int posY = (int)(currentPos.y / cellSize.y);

		if (!isStartInput)
		{
			isStartInput = true;
			startPosition = { cellSize.x * posX , cellSize.y * posY };
		}
		else
		{
			isEndInput = true;
			endPosition = { cellSize.x * posX , cellSize.y * posY };
		}
	}

	if (ImGui::Button("Start Input Create", { 200.f,20.f }))
		isCreateObject = !isCreateObject;

	if (isCreateObject)
	{
		float startPositionArr[2] = { startPosition.x, startPosition.y };
		float endPositionArr[2] = { endPosition.x, endPosition.y };
		ImGui::Text("StartPosition"); ImGui::SameLine();
		if (ImGui::InputFloat2("##StartPosition", startPositionArr))
		{
			if (startPositionArr[0] > 0.f && startPositionArr[1] > 0.f)
			{
				startPosition.x = startPositionArr[0];
				startPosition.y = startPositionArr[1];
			}
		}

		ImGui::Text("EndPosition"); ImGui::SameLine();
		if (ImGui::InputFloat2("##EndPosition", endPositionArr))
		{
			if (endPositionArr[0] > 0.f && endPositionArr[1] > 0.f)
			{
				endPosition.x = endPositionArr[0];
				endPosition.y = endPositionArr[1];
			}
		}
	}

	if (ImGui::Button("Reset", { 50.f,20.f }))
	{
		isStartInput = false;
		isEndInput = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Create", { 50.f,20.f }))
	{
		if (isStartInput && isEndInput)
		{
			isStartInput = false;
			isEndInput = false;

			sf::Vector2f pos = endPosition - startPosition;
			auto object = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new WallCollisionObject, LayerType::TileMap);
			object->SetPosition(startPosition + (pos * 0.5f));
			pos = { abs(pos.x), abs(pos.y) };
			object->SetScale(pos);
			object->Start();
		}
	}

	if (!isCreateObject)
	{
		isStartInput = false;
		isEndInput = false;
	}

	ImGui::End();
}

