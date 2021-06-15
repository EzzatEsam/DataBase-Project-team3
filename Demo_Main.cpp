#include "Battle.h"
#include "GUI\GUI.h"
#include "Generic_DS/MaxHeap.h"
#include "Defs.h"
using namespace std;
int main()
{
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	delete pGameBattle;
	return 0;
	/*MaxHeap<Enemy*> Fighters;
	for (int i = 0; i < 8; i++)
	{
		Fighter* f1 = new Fighter(i,i, i, i, i, i);
		f1->SetStatus(ACTV);
		Fighters.insert(f1);
	}
	
	

	Enemy* tst;

	
	
	
	int n = 0;
	while (Fighters.BeHead(tst)) {
		n++;
		auto x = tst->getPriority();
	}*/
	

	



	
}
