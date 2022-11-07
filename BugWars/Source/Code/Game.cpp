#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
	for(int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if ((i + 1) < 100)
			{
				gameMap[i][j].upNeighbor = &gameMap[i + 1][j];

				if ((j + 1) < 100)
					gameMap[i][j].RUDNeighbor = &gameMap[i + 1][j + 1];
				else
					gameMap[i][j].RUDNeighbor = nullptr;

				if ((j - 1) > -1)
					gameMap[i][j].LUDNeighbor = &gameMap[i + 1][j - 1];
				else
					gameMap[i][j].LUDNeighbor = nullptr;
			}
			else
				gameMap[i][j].upNeighbor = nullptr;

			if ((j + 1) < 100)
				gameMap[i][j].rightNeighbor = &gameMap[i][j + 1];
			else
				gameMap[i][j].rightNeighbor = nullptr;

			if ((i - 1) > -1)
			{
				gameMap[i][j].downNeighbor = &gameMap[i - 1][j];

				if ((j + 1) < 100)
					gameMap[i][j].RDDNeighbor = &gameMap[i - 1][j + 1];
				else
					gameMap[i][j].RDDNeighbor = nullptr;

				if ((j - 1) > -1)
					gameMap[i][j].LDDNeighbor = &gameMap[i - 1][j - 1];
				else
					gameMap[i][j].LDDNeighbor = nullptr;
			}
			else
				gameMap[i][j].downNeighbor = nullptr;

			if ((j - 1) > -1)
				gameMap[i][j].leftNeighbor = &gameMap[i][j - 1];
			else
				gameMap[i][j].leftNeighbor = nullptr;
		}
	}
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (GameObject* obj : objects)
		if (!obj->disabled)
			obj->Update(dt);

}

void Game::OnRender() const
{
	for (GameObject* obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
	int indX = static_cast<int>(trunc(object->position.x));
	int indY = static_cast<int>(trunc(object->position.y));
	gameMap[indX][indY].objects.push_back(object);
//	if (object->GetRTTI() == Bug::s_RTTI)
	//	Log("I'm a bug");
}

void Game::OnBugsSpawned()
{

}

Game::~Game()
{
	for (GameObject* obj : objects)
		delete(obj);
}