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
	MaxHeap<int> test;
	test.insert(5);
	test.insert(4);
	test.insert(10);
	test.insert(3);
	test.insert(6);
	test.insert(8);
	test.insert(7);
	int x;
	while (test.BeHead(x))
	{
		cout << x;
	}
	cout << "sds";
}
