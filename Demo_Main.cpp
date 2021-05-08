#include "Battle.h"
#include "GUI\GUI.h"

using namespace std;
int main()
{
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	delete pGameBattle;
	return 0;
}
