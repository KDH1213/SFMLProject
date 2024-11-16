#pragma once
#include "Enemy.h"
#include "GoombaFSM.h"
class Goomba : public Enemy
{
public:
	void Awake() override;
	void Start() override;

public:
	Goomba(const std::string& name = "Goomba");
	virtual ~Goomba();
};

