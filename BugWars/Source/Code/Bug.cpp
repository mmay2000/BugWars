#include "pch.h"
#include "Bug.h"
#include "Game.h"
#include <queue>

IMPLEMENT_RTTI(Bug);


Bug::Bug()
{
	visible = true;
	disabled = false;
}

void Bug::OnUpdate(float dt)
{
	
}

BugBase* Bug::FindBugToEat() const
{
	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	
	int indX, indY, D1X, D1Y, D4X, D4Y;
	indX = static_cast<int>(trunc(position.x)) / 100;
	indY = static_cast<int>(trunc(position.y)) / 100;
	D1X = indX;
	D4X = indX;
	D1Y = indY;
	D4Y = indY;
	bool done = false;
	std::queue<Game::cell*> right, left, up, down, RUD, LUD, RDD, LDD;


	for (GameObject* object : g_Game->gameMap[indX][indY].objects)
	{
		if (object->GetRTTI() == Bug::s_RTTI)
		{
			if (object == this)
				continue;

			if (object->disabled)
				continue;

			if (object->id > id)
				continue; // Can't eat that

			float dist = position.Distance(object->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = static_cast<Bug*>(object);
			}
		}
	}

	if (target != nullptr)
		done = true;

	while (!done)
	{

		if (D1X - 1 >= 0)
		{
			D1X--;
		}

		if (D1Y - 1 >= 0)
		{
			D1Y--;
		}

		if (D4X + 1 < 100)
		{
			D4X++;
		}

		if (D4Y + 1 < 100)
		{
			D4Y++;
		}

		for (int i = D1X; i <= D4X; ++i)
		{
			for (GameObject* object : g_Game->gameMap[i][D1Y].objects)
			{
				if (object->GetRTTI() == Bug::s_RTTI)
				{
					if (object == this)
						continue;

					if (object->disabled)
						continue;

					if (object->id > id)
						continue; // Can't eat that

					float dist = position.Distance(object->position);
					if (dist < min_dist)
					{
						min_dist = dist;
						target = static_cast<Bug*>(object);
					}
				}
			}

			for (GameObject* object : g_Game->gameMap[i][D4Y].objects)
			{
				if (object->GetRTTI() == Bug::s_RTTI)
				{
					if (object == this)
						continue;

					if (object->disabled)
						continue;

					if (object->id > id)
						continue; // Can't eat that

					float dist = position.Distance(object->position);
					if (dist < min_dist)
					{
						min_dist = dist;
						target = static_cast<Bug*>(object);
					}
				}
			}
		}

		for (int i = D1Y + 1; i <= D4Y - 1; ++i)
		{
			for (GameObject* object : g_Game->gameMap[D1X][i].objects)
			{
				if (object->GetRTTI() == Bug::s_RTTI)
				{
					if (object == this)
						continue;

					if (object->disabled)
						continue;

					if (object->id > id)
						continue; // Can't eat that

					float dist = position.Distance(object->position);
					if (dist < min_dist)
					{
						min_dist = dist;
						target = static_cast<Bug*>(object);
					}
				}
			}

			for (GameObject* object : g_Game->gameMap[D4Y][i].objects)
			{
				if (object->GetRTTI() == Bug::s_RTTI)
				{
					if (object == this)
						continue;

					if (object->disabled)
						continue;

					if (object->id > id)
						continue; // Can't eat that

					float dist = position.Distance(object->position);
					if (dist < min_dist)
					{
						min_dist = dist;
						target = static_cast<Bug*>(object);
					}
				}
			}
		}


		if ((target != nullptr))
			done = true;

		if ((D1X == 0) && (D1Y == 0) && (D4X == 99) && (D4Y == 99))
			return nullptr;
	}

	if (D1X - 1 >= 0)
	{
		D1X--;
	}

	if (D1Y - 1 >= 0)
	{
		D1Y--;
	}

	if (D4X + 1 < 100)
	{
		D4X++;
	}

	if (D4Y + 1 < 100)
	{
		D4Y++;
	}

	for (int i = D1X; i <= D4X; ++i)
	{
		for (GameObject* object : g_Game->gameMap[i][D1Y].objects)
		{
			if (object->GetRTTI() == Bug::s_RTTI)
			{
				if (object == this)
					continue;

				if (object->disabled)
					continue;

				if (object->id > id)
					continue; // Can't eat that

				float dist = position.Distance(object->position);
				if (dist < min_dist)
				{
					min_dist = dist;
					target = static_cast<Bug*>(object);
				}
			}
		}

		for (GameObject* object : g_Game->gameMap[i][D4Y].objects)
		{
			if (object->GetRTTI() == Bug::s_RTTI)
			{
				if (object == this)
					continue;

				if (object->disabled)
					continue;

				if (object->id > id)
					continue; // Can't eat that

				float dist = position.Distance(object->position);
				if (dist < min_dist)
				{
					min_dist = dist;
					target = static_cast<Bug*>(object);
				}
			}
		}
	}

	for (int i = D1Y + 1; i <= D4Y - 1; ++i)
	{
		for (GameObject* object : g_Game->gameMap[D1X][i].objects)
		{
			if (object->GetRTTI() == Bug::s_RTTI)
			{
				if (object == this)
					continue;

				if (object->disabled)
					continue;

				if (object->id > id)
					continue; // Can't eat that

				float dist = position.Distance(object->position);
				if (dist < min_dist)
				{
					min_dist = dist;
					target = static_cast<Bug*>(object);
				}
			}
		}

		for (GameObject* object : g_Game->gameMap[D4Y][i].objects)
		{
			if (object->GetRTTI() == Bug::s_RTTI)
			{
				if (object == this)
					continue;

				if (object->disabled)
					continue;

				if (object->id > id)
					continue; // Can't eat that

				float dist = position.Distance(object->position);
				if (dist < min_dist)
				{
					min_dist = dist;
					target = static_cast<Bug*>(object);
				}
			}
		}
	}
	/*
	for (GameObject* object : g_Game->objects)
	{
		if (object->GetRTTI() == Bug::s_RTTI)
		{
			if (object == this)
				continue;

			if (object->disabled)
				continue;

			if (object->id > id)
				continue; // Can't eat that

			float dist = position.Distance(object->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = static_cast<Bug*>(object);
			}
		}
	}
	*/


	return target;
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	if (first.id > second.id)
	{
		second.disabled = true;
		second.visible = false;
		
	}
	else
	{
		first.disabled = true;
		first.visible = false;
	}
}
