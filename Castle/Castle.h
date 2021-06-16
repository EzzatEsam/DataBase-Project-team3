#pragma once
#include "..\Defs.h"
#include "../Enemies/Enemy.h"
class Castle
{
	double Health;
	int AtkNum;
	int AtkDamage;

	//
	// TODO: Add More Data Members As Needed
	//
	//int N; // Enemies to be attacked one time step
	//int firePower;
	double takenFreeze;
	bool Frozen = false;
	double Accumelated_Freezing_Amount = 25;

public:
	int Freezing_Step = 0;
	double MaxHealth;

	float castleTotalDamage = 0;
	float totalDmgTaken = 0;
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
	void Fire(Enemy *, int CurrentTimeStep);
	bool Freeze(Enemy *, int CurrentTimeStep);

	void setFreezengAmount(double val);
	double getFreezingAmount();

	void setFrozen(bool val);
	bool getFrozen();

	double getMaxFreezeAmount();
	int getN();
};
