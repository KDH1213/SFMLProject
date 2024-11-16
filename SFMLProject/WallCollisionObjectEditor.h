#pragma once

#include "GUI.h"

class WallCollisionObjectEditor : public GUI
{
protected:
    sf::Vector2f	cellSize;
    sf::Vector2f    startPosition;
    sf::Vector2f    endPosition;

    bool            isCreateObject;
    bool            isStartInput;
    bool            isEndInput;

public:
    void Init() override;
    void Update() override;

public:
    WallCollisionObjectEditor();
    ~WallCollisionObjectEditor();
};

