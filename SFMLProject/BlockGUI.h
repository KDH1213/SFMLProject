#pragma once

#include "ComponentGUI.h"
#include "imgui.h"

class BlockObject;

class BlockGUI : public ComponentGUI
{
protected:
	BlockObject*	blockObject;
	sf::Texture*	texture;
	ImVec2			tileUvSize;
	bool			isChangeRect;	
	int				heightCount;
	int				widthCount;

public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	BlockGUI();
	~BlockGUI();
};

