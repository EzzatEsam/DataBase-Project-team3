#include "Healer.h"
Healer::Healer(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d) :
	Enemy(id, arrTime, health, spd, firePower, reloadPerioud, d)
{
}

Healer::~Healer()
{


void Healer::Move()
{
	// If the health is half then the speed is halved as well
	int moveSpd = Speed;
	if (Health < MaxHealth / 2)
		moveSpd /= 2;

	// Backward Movement
	if (Distance == MinDistance)
		MoveBackwardFlag = true;

	if (MoveBackwardFlag) {
		if (Distance == MaxDistance)
			MoveBackwardFlag = false;
		else 
			Distance = (Distance + moveSpd > MaxDistance) ? 60 : Distance + moveSpd;
	}
	else
		decDistanceByFactor(moveSpd);

}

void Healer::Act()
{
	// Assume we are looping on all enemies with pointer pE
	Enemy* pE;
	
	// Forward Direction Healer
	if (!MoveBackwardFlag && !(Distance - pE->GetDistance() <= 2)) {
		//break;
	}
	else if (MoveBackwardFlag && !(pE->GetDistance() - Distance <= 2)) {
		//break;
	}
	else {
		// Heal in this case 
		if (pE->GetStatus() != FRST) {
			double addedHealth = Health / 10 + pE->getHealth() / 10 + abs(Distance - pE->GetDistance());
			pE->increaseHealth(addedHealth);
		}
	}

}
