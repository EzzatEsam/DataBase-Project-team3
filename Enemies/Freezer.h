#pragma once
#include"Enemy.h"
class Freezer : public Enemy
{
private:
	bool MoveBackwardFlag = false;
public:
	Freezer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d = MaxDistance);
	virtual ~Freezer();

	virtual void Move();
	virtual void Act();
};
