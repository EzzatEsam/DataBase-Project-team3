#include "Battle.h"
#include "GUI\GUI.h"
#include "Generic_DS/MaxHeap.h"
using namespace std;
int main()
{
	/*Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	delete pGameBattle;
	return 0;*/

	Fighter f1(1,1,1,1,1,1);
	Fighter f2(2,2,2,2,2,2);

	Enemy* tst;

	MaxHeap<Enemy*> Fighters;
	Fighters.insert(&f1);
	Fighters.insert(&f2);

	Fighters.BeHead(tst);
	double pri = tst->getPriority();

	Fighters.BeHead(tst);
	double pri2 = tst->getPriority();


	/*MaxHeap<int> test;
	test.insert(5);
	test.insert(4);
	test.insert(10);
	test.insert(3);
	test.insert(6);
	test.insert(8);
	test.insert(7);
	test.RefreshTheHeap();
	int x;
	while (test.BeHead(x))
	{
		cout << x;
	}
	cout << "sds";*/
}
