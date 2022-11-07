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

	if (min_dist > 200.f)
		target = nullptr;
	return target;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	Point meetingDir = target_pos - position;

	if (meetingDir.x * target_dir.y == meetingDir.y * target_dir.x)
		return meetingDir;
	
	meetingDir = (target_pos - position) * 1.5f -  target_dir * target_vel / bullet_vel / 2.0f;
	meetingDir = meetingDir + target_dir * target_vel * (position.Distance(target_pos) / bullet_vel);
	return meetingDir;
}
