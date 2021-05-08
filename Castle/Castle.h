#pragma once
#include "..\Defs.h"
#include"../Enemies/Enemy.h"
#include"../Enemies/Healer.h"
class Castle
{
	double Health;
	//
	// TODO: Add More Data Members As Needed
	//
	int N; // Enemies to be attacked one time step
	int firePower;

public:

	void SetHealth(double h);
	double GetHealth() const;

	//
	// TODO: Add More Member Functions As Needed
	//

	void Fire(Enemy*);
	void Freeze(Enemy*);
};

