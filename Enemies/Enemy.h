#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;		//Each enemy has a unique ID (sequence number)
	const int ArrvTime; //arrival time (time it starts to join battle)
	
	ENMY_STATUS status; //status of the enemy (inactive, inactive, frosted, killed)
	double Distance;	//Horizontal distance between enemy & the tower of its region
						//Always positive (ranges from 2 to 60)
	double Health;		//Enemy health
	double MaxHealth;
	// TODO: Add More Data Members As Needed
	int Speed;
	int FirePower;

public:
	int ReloadPeriod;
	int ReloadPerioudTmp;

	int DeathTime = -1;
	int FirstShotTime = -1;
	int Frost_Time_Steps = 0;

	Enemy(int id, int arrTime, double d = MaxDistance);
	Enemy(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d = MaxDistance);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();
	
	void SetDistance(int);
	int GetDistance() const;
	int GetDeathTime() const;
	int GetArrvTime() const;
	int GetFirstShotTime() const { return FirstShotTime; }
	// Virtual Functions: ----------------

	virtual void Move() = 0; //All enemies can move
	virtual void Act() = 0;	 //Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	void decDistanceByFactor(double factor);
	double getPriority() const
	{
		if (status == KILD || status == INAC )
		{
			return 0;
		}
		return ((status == ACTV) ? 1 : 0.5) * (FirePower) / (this->Distance * Health);
	}


	void setHealth(double val);
	double getHealth();
	void increaseHealth(double val);
	bool operator > (Enemy const& obj) {
		
		return this->getPriority() >obj.getPriority();
	}
	bool operator < (Enemy const& obj) {

		return this->getPriority() < obj.getPriority();
	}
	bool operator == (Enemy const& obj) {

		return this->getPriority() == obj.getPriority();
	}
};
