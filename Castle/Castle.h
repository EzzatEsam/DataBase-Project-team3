#pragma once
#include "..\Defs.h"
#include"../Enemies/Enemy.h"
class Castle
{
	double Health;
	int AtkNum;
	int AtkDamage;

	//
	// TODO: Add More Data Members As Needed
	//
	int N; // Enemies to be attacked one time step
	int firePower;
	double takenFreeze;
	bool Frozen = false;

public:
	Castle(double health_i);
	Castle();
	void SetAtkNum(int);
	void SetAtkDamage(int);
	void SetHealth(double h);
	double GetHealth() const;
	int GetAtkDamage() const;
	int GetAtkNum() const;

	//
	// TODO: Add More Member Functions As Needed
	//
	void Fire(Enemy *);
	void Freeze(Enemy *);

	void setFreezengAmount(double val);
	double getFreezingAmount();

	void setFrozen(bool val);
};
