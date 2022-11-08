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
	
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (GameObject* obj : objects)
		if (!obj->disabled)
		{
			int indX = static_cast<int>(trunc(obj->position.x) / 100);
			int indY = static_cast<int>(trunc(obj->position.y) / 100);
			for (GameObject* object : gameMap[indX][indY].objects)
				if (obj->id == object->id)
					object = nullptr;
			obj->Update(dt);
			indX = static_cast<int>(trunc(obj->position.x) / 100);
			indY = static_cast<int>(trunc(obj->position.y) / 100);
			gameMap[indX][indY].objects.push_back(obj);
		}

	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
			gameMap[i][j].objects.clear();

	for (GameObject* obj : objects)
		if (!obj->disabled)
		{
			int indX = static_cast<int>(trunc(obj->position.x) / 100);
			int indY = static_cast<int>(trunc(obj->position.y) / 100);
			gameMap[indX][indY].objects.push_back(obj);
		}

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
	int indX = static_cast<int>(trunc(object->position.x))/100;
	int indY = static_cast<int>(trunc(object->position.y))/100;
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