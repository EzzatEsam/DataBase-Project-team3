#include"Enemy.h"
class Fighter : public Enemy
{
private:
	
public:
	Fighter(int id, int arrTime, double health, int spd, int firePower, int reloadPerioud, double d = MaxDistance);
	virtual ~Fighter();

	virtual void Move();
	virtual void Act();
};
