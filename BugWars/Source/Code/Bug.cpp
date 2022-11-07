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
	
	int indX, indY;
	indX = static_cast<int>(trunc(position.x));
	indY = static_cast<int>(trunc(position.y));
	bool done = false;
	std::queue<Game::cell*> right, left, up, down, RUD, LUD, RDD, LDD;


	for(GameObject* object : g_Game->gameMap[indX][indY].objects)
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
	right.push(g_Game->gameMap[indX][indY].rightNeighbor);
	left.push(g_Game->gameMap[indX][indY].leftNeighbor);
	up.push(g_Game->gameMap[indX][indY].upNeighbor); 
	down.push(g_Game->gameMap[indX][indY].downNeighbor); 
	RUD.push(g_Game->gameMap[indX][indY].RUDNeighbor);
	LUD.push(g_Game->gameMap[indX][indY].LUDNeighbor);
	RDD.push(g_Game->gameMap[indX][indY].RDDNeighbor);
	LDD.push(g_Game->gameMap[indX][indY].LDDNeighbor);

	int areaEdge = 1;
	bool allArea;

	while (!done)
	{
		allArea = true;

		if (!right.empty())
		{
			for (int i = 0; i < areaEdge; ++i)
			{
				if (!right.front()->objects.empty())
				{
					for (GameObject* object : right.front()->objects)
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
					if (right.front()->downNeighbor != nullptr)
						right.push(right.front()->rightNeighbor);
					right.pop();
				}
			}
			allArea = false;
		}

		if (!left.empty())
		{
			for (int i = 0; i < areaEdge; ++i)
			{
				if (!left.front()->objects.empty())
				{
					for (GameObject* object : left.front()->objects)
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
					if (left.front()->leftNeighbor != nullptr)
						left.push(left.front()->leftNeighbor);
					left.pop();
				}
			}
			allArea = false;
		}

		if (!up.empty())
		{
			for (int i = 0; i < areaEdge; ++i)
			{
				if (!up.front()->objects.empty())
				{
					for (GameObject* object : up.front()->objects)
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
					if (up.front()->upNeighbor != nullptr)
						up.push(up.front()->upNeighbor);
					up.pop();
				}
			}
			allArea = false;
		}

		if (!down.empty())
		{
			for (int i = 0; i < areaEdge; ++i)
			{
				if (!down.front()->objects.empty())
				{
					for (GameObject* object : down.front()->objects)
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
					if (down.front()->downNeighbor != nullptr)
						down.push(down.front()->downNeighbor);
					down.pop();
				}
			}
			allArea = false;
		}

		if (!RUD.empty())
		{
			if (!RUD.front()->objects.empty())
			{
				for (GameObject* object : RUD.front()->objects)
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
				if (RUD.front()->RUDNeighbor != nullptr)
					RUD.push(RUD.front()->RUDNeighbor);
				if (RUD.front()->rightNeighbor != nullptr)
					right.push(RUD.front()->rightNeighbor);
				if (RUD.front()->upNeighbor != nullptr)
					up.push(RUD.front()->upNeighbor);
				RUD.pop();
			}
		}

		if (!LUD.empty())
		{
			if (!LUD.front()->objects.empty())
			{
				for (GameObject* object : LUD.front()->objects)
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
				if (LUD.front()->LUDNeighbor != nullptr)
					LUD.push(LUD.front()->LUDNeighbor);
				if (LUD.front()->leftNeighbor != nullptr)
					left.push(LUD.front()->leftNeighbor);
				if (LUD.front()->upNeighbor != nullptr)
					up.push(LUD.front()->upNeighbor);
				LUD.pop();
			}
		}

		if (!RDD.empty())
		{
			if (!RDD.front()->objects.empty())
			{
				for (GameObject* object : RDD.front()->objects)
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
				if (RDD.front()->RDDNeighbor != nullptr)
					RDD.push(RDD.front()->RDDNeighbor);
				if (RDD.front()->rightNeighbor != nullptr)
					right.push(RDD.front()->rightNeighbor);
				if (RDD.front()->downNeighbor != nullptr)
					down.push(RDD.front()->downNeighbor);
				RDD.pop();
			}
		}

		if (!LDD.empty())
		{
			if (!LDD.front()->objects.empty())
			{
				for (GameObject* object : LDD.front()->objects)
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
				if (LDD.front()->LDDNeighbor != nullptr)
					LDD.push(LDD.front()->LDDNeighbor);
				if (LDD.front()->leftNeighbor != nullptr)
					left.push(LDD.front()->leftNeighbor);
				if (LDD.front()->downNeighbor != nullptr)
					down.push(LDD.front()->downNeighbor);
				LDD.pop();
			}
		}

		if ((target != nullptr)||(allArea))
			done = true;

		areaEdge += 2;
	} 



	if (!right.empty())
	{
		for (int i = 0; i < areaEdge; ++i)
		{
			if (!right.front()->objects.empty())
			{
				for (GameObject* object : right.front()->objects)
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
				right.pop();
			}
		}
	}

	if (!left.empty())
	{
		for (int i = 0; i < areaEdge; ++i)
		{
			if (!left.front()->objects.empty())
			{
				for (GameObject* object : left.front()->objects)
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
				left.pop();
			}
		}
	}

	if (!up.empty())
	{
		for (int i = 0; i < areaEdge; ++i)
		{
			if (!up.front()->objects.empty())
			{
				for (GameObject* object : up.front()->objects)
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
				up.pop();
			}
		}
	}

	if (!down.empty())
	{
		for (int i = 0; i < areaEdge; ++i)
		{
			if (!down.front()->objects.empty())
			{
				for (GameObject* object : down.front()->objects)
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
				down.pop();
			}
		}
	}

	if (!RUD.empty())
	{
		if (!RUD.front()->objects.empty())
		{
			for (GameObject* object : RUD.front()->objects)
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
	}

	if (!LUD.empty())
	{
		if (!LUD.front()->objects.empty())
		{
			for (GameObject* object : LUD.front()->objects)
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
	}

	if (!RDD.empty())
	{
		if (!RDD.front()->objects.empty())
		{
			for (GameObject* object : RDD.front()->objects)
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
	}

	if (!LDD.empty())
	{
		if (!LDD.front()->objects.empty())
		{
			for (GameObject* object : LDD.front()->objects)
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
