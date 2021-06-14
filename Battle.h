#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS\Stack.h"
#include "Generic_DS\PriorityQueue.h"
#include "GUI\GUI.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount = 0,FighterCount=0 ,HealerCount=0,FreezerCount=0,frozenCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int FrostedFighter = 0, FrostedHealer = 0, FrostedFreezer = 0;
	int KilledFighter = 0, KilledHealer = 0, KilledFreezer = 0;

	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies


	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	//int DemoListCount;
	//Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo

	// || \\

	PriorityQueue<Enemy*,int> Fighters;
	Queue<Enemy*> freezers , Frozen, dead;
	Stack<Enemy*> healers;




	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void SetEnemyCount(int);
	void InteractiveSimulation();   // phase 1 simple simulation func
	void AddByType(Enemy *);
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	void UpdateEnemies();

	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)

	Queue<string> Convert2Strings();
	//
	// TODO: Add More Member Functions As Needed
	//
};

