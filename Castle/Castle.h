#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int AtkNum;
	int AtkDamage;

	//
	// TODO: Add More Data Members As Needed
	//

public:

	void SetAtkNum(int);
	void SetAtkDamage(int);
	void SetHealth(double h);
	double GetHealth() const;
	int GetAtkDamage() const;
	int GetAtkNum() const;

	//
	// TODO: Add More Member Functions As Needed
	//

};

