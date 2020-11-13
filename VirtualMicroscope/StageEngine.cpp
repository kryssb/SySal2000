#include "StdAfx.h"
#include "StageEngine.h"
#include <math.h>

StageEngine::StageEngine()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		Axes[i].Current.Pos = 0;
		Axes[i].Current.Time = GetTickCount();
		Axes[i].Target.IsValid = false;
		};
	Light = 0;
	};

void StageEngine::Evolve(unsigned axis)
{
	if (!Axes[axis].Target.IsValid) return;
	unsigned time = GetTickCount();
	if (!Axes[axis].Target.IsSpeed && (time >= Axes[axis].Target.EndTime)) 
	{
		Axes[axis].Current.Pos = Axes[axis].Target.Pos;
		}
	else if (Axes[axis].Target.IsSpeed)
	{
		Axes[axis].Current.Pos = (time - Axes[axis].Target.StartTime) * .001f * Axes[axis].Target.Speed + Axes[axis].Target.StartPos;
		}
	else 
	{
		float x = (float)(time - Axes[axis].Target.StartTime) / (float)(Axes[axis].Target.EndTime - Axes[axis].Target.StartTime);
		Axes[axis].Current.Pos = x * Axes[axis].Target.Pos + (1. - x) * Axes[axis].Target.StartPos;
		};
	Axes[axis].Current.Time = time;
	};

bool StageEngine::PosMove(unsigned axis, float pos, float speed, float acc)
{
	if (axis > 2) return false;
	if (speed == 0.f) return false;
	Evolve(axis);
	Axes[axis].Target.IsValid = true;
	Axes[axis].Target.IsSpeed = false;
	Axes[axis].Target.StartPos = Axes[axis].Current.Pos;
	Axes[axis].Target.StartTime = Axes[axis].Current.Time = GetTickCount();
	Axes[axis].Target.Acc = acc;
	Axes[axis].Target.Pos = pos;
	Axes[axis].Target.Speed = fabs(speed);
	Axes[axis].Target.EndTime = Axes[axis].Target.StartTime + fabs(pos - Axes[axis].Target.StartPos) / fabs(Axes[axis].Target.Speed) * 1000.f;
	return true;
	};
		
bool StageEngine::SpeedMove(unsigned axis, float speed, float acc)
{
	if (axis > 2) return false;
	Evolve(axis);
	Axes[axis].Target.IsValid = true;
	Axes[axis].Target.IsSpeed = true;
	Axes[axis].Target.StartPos = Axes[axis].Current.Pos;
	Axes[axis].Target.StartTime = Axes[axis].Current.Time = GetTickCount();
	Axes[axis].Target.Acc = acc;
	Axes[axis].Target.Pos = Axes[axis].Target.StartPos;
	Axes[axis].Target.Speed = speed;
	Axes[axis].Target.EndTime = Axes[axis].Target.StartTime;
	return true;
	};
		
bool StageEngine::Stop(unsigned axis)
{
	if (axis > 2) return false;
	Evolve(axis);
	Axes[axis].Target.IsValid = false;
	return true;
	};
		
bool StageEngine::Reset(unsigned axis)
{
	if (axis > 2) return false;
	Axes[axis].Current.Pos = 0.f;
	if (Axes[axis].Target.IsValid)
	{
		Axes[axis].Target.IsValid = false;
		if (Axes[axis].Target.IsSpeed) SpeedMove(axis, Axes[axis].Target.Speed, Axes[axis].Target.Acc);
		else PosMove(axis, Axes[axis].Target.Pos, Axes[axis].Target.Speed, Axes[axis].Target.Acc);
		};
	return true;
	};
		
bool StageEngine::GetPos(unsigned axis, float &pos)
{
	if (axis > 2) return false;
	Evolve(axis);
	pos = Axes[axis].Current.Pos;
	return true;
	};
		
bool StageEngine::GetTarget(unsigned axis, AxisInfo::t_Target &t)
{
	if (axis > 2) return false;
	t = Axes[axis].Target;
	return true;
	};

void StageEngine::SetLight(unsigned short light)
{
	Light = light;
	};

void StageEngine::GetLight(unsigned short &light)
{
	light = Light;
	};
