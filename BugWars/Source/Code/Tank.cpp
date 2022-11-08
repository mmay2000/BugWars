#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);


Tank::Tank()
{
	visible = true;
	disabled = false;
}

void Tank::OnUpdate(float dt)
{

}

BugBase* Tank::GetBugToShoot() const
{
	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	/*
	int indX, indY, D1X, D1Y, D4X, D4Y;
	indX = static_cast<int>(trunc(position.x)) / 100;
	indY = static_cast<int>(trunc(position.y)) / 100;
	D1X = indX;
	D4X = indX;
	D1Y = indY;
	D4Y = indY;
	bool done = false;


	for (GameObject* object : g_Game->gameMap[indX][indY].objects)
	{
		if (object->GetRTTI() == Bug::s_RTTI)
		{
			if (object->disabled)
				continue;

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
					if (object->disabled)
						continue;

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
					if (object->disabled)
						continue;

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
					if (object->disabled)
						continue;

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
					if (object->disabled)
						continue;

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
				if (object->disabled)
					continue;

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
				if (object->disabled)
					continue;

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
				if (object->disabled)
					continue;

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
				if (object->disabled)
					continue;

				float dist = position.Distance(object->position);
				if (dist < min_dist)
				{
					min_dist = dist;
					target = static_cast<Bug*>(object);
				}
			}
		}
	}
	*/
	
	for (GameObject* object : g_Game->objects)
	{
		if (object->GetRTTI() == Bug::s_RTTI)
		{
			if (object->disabled)
				continue;

			float dist = position.Distance(object->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = static_cast<Bug*>(object);
			}
		}
	}
	
	return target;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	
	Point meetingDir = target_pos - position;

	if (meetingDir.x * target_dir.y == meetingDir.y * target_dir.x)
		return meetingDir;
	
	
	float c = position.Distance2(target_pos);
	float b = 2.f * target_vel 
		* ((target_pos.x - position.x) * target_dir.Normalized().x + (target_pos.y - position.y) * target_dir.Normalized().y);
	float a = target_vel * target_vel - bullet_vel * bullet_vel;

	float D = b * b - 4 * a * c;

	float t1 = (-b + sqrt(D)) / (2.f * a);
	float t2 = (-b - sqrt(D)) / (2.f * a);
	float t = (t1 > t2) ? t1 : t2;

	Point meetingPoint = target_pos + target_dir.Normalized() * t * target_vel;

	meetingDir = meetingPoint - position;
	
	return meetingDir;

	
}
