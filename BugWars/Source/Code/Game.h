#pragma once
#include "GameBase/GameBase.h"
#include "Globals.h"

struct Tank;

struct Game : public GameBase
{
	Game();

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() const override;
	virtual void AddObject(GameObject* object) override;

	virtual void OnBugsSpawned() override;

	~Game();

	std::vector<GameObject*> objects;

public:

	struct cell
	{
		std::vector<GameObject*> objects;
	};

	cell gameMap[100][100];
};