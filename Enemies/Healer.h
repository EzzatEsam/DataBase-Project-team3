#pragma once
#include"Enemy.h"
class Healer : public Enemy
{
private:
	bool MoveBackwardFlag = false;
public:
	Healer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d = MaxDistance);
	virtual ~Healer();

	virtual void Move();
	virtual void Act();
};

