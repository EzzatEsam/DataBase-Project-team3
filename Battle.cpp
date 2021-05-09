#include "Battle.h"
#include <time.h>
#include "FileManager.h"
#include <iostream>
Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	
	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InteractiveSimulation();
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	}

	delete pGUI;
	
}

void Battle::SetEnemyCount(int n)
	{
			EnemyCount = n;
	}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{	
	
	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//
	 
	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime=1;
	Enemy* pE= NULL;
	//Create Random enemies and add them all to inactive queue
	for(int i=0; i<EnemyCount; i++)
	{			
		ArrivalTime += (rand()%3);	//Randomize arrival time
		//pE = new Enemy(++Enemy_id,ArrivalTime);
		pE->SetStatus( INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}	

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	
	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
		Sleep(250);
	}		
}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//
	int count;
	Enemy* const* fightersarr = Fighters.toArray(count);
	for (int i = 0; i < count; i++)
	{
		std::cout << "f" << endl;
		pGUI->AddToDrawingList(fightersarr[i]);
	}
	Enemy* const* healersarr = healers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(healersarr[i]);
		std::cout << "h" << endl;

	}
	Enemy* const* freezersarr = freezers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(freezersarr[i]);
		std::cout << "fr" << endl;

	}
	Enemy* const* ded = dead.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(ded[i]);
		std::cout << "dd" << endl;

	}
	Enemy* const* frz = Frozen.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(frz[i]);
		std::cout << "fz" << endl;
	}
	

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	/*for(int i=0; i<DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);*/
}

void Battle::InteractiveSimulation()
{
	FileManager mngr(this);
	pGUI->PrintMessage("Please enter file name");
	here:
	try
	{
		Q_Inactive = mngr.GetInput(pGUI->GetString());
	}
	catch (...)
	{
		pGUI->PrintMessage("Invalid input... please enter the name again");
		goto here;
	}
	
	CurrentTimeStep = 0;
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
	pGUI->waitForClick();

	//
	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
		pGUI->waitForClick();
	}

}

void Battle::AddByType(Enemy * pE)
{
	if (dynamic_cast<const Fighter*>(pE))
	{
		Fighters.enqueue(pE,0);
		FighterCount++;
	}
	else if (dynamic_cast<const Healer*>(pE))
	{
		healers.push(pE);
		HealerCount++;
	}
	else
	{
		freezers.enqueue(pE);
		FreezerCount++;
	}
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddByType(pE);		//move it to the corrosponding ds
	}
}

void Battle::UpdateEnemies()
{
	
	int count;
	Enemy* const* fightersarr  = Fighters.toArray(count);
	for (int i = 0; i < count; i++)
	{
		fightersarr[i]->Move();
		//fightersarr[i]->Act();
	}
	Enemy* const* healersarr = healers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		healersarr[i]->Move();
		//healersarr[i]->Act();
	}
	Enemy* const* freezersarr = freezers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		freezersarr[i]->Move();
		//freezersarr[i]->Act();
	}
	Enemy* temp;
	//freezing two of each type
	for (int i = 0; i < 2; i++)
	{
		
		if(Fighters.dequeue(temp)){
			FighterCount--;
			frozenCount++;
			Frozen.enqueue(temp);
			temp->SetStatus(FRST);
			FrostedFighter++;
		}
		
		if (healers.pop(temp))
		{
			HealerCount--;
			frozenCount++;
			Frozen.enqueue(temp);
			temp->SetStatus(FRST);
			FrostedHealer++;
		}
		if (freezers.dequeue(temp))
		{
			FreezerCount--;
			frozenCount++;
			Frozen.enqueue(temp);
			temp->SetStatus(FRST);
			FrostedFreezer++;
		}
	}

	for (int i = 0; i < 2; i++)		  //defreezing 2

	{
		if (Frozen.dequeue(temp))
		{
			if (dynamic_cast<const Fighter*>(temp))
			{
				Fighters.enqueue(temp, 0);
				FighterCount++;
				temp->SetStatus(ACTV);
				FrostedFighter--;
			}
			else if (dynamic_cast<const Healer*>(temp))
			{
				healers.push(temp);
				HealerCount++;
				temp->SetStatus(ACTV);
				FrostedHealer--;
			}
			else
			{
				freezers.enqueue(temp);
				FreezerCount++;
				temp->SetStatus(ACTV);
				FrostedFreezer--;
			}
			frozenCount--;
		}
	}
	if (Fighters.dequeue(temp))   //killing one fighter
	{
		dead.push(temp);
		FighterCount--;
		KilledCount++;
		KilledFighter++;
		temp->SetStatus(KILD);
	}
	else if (healers.pop(temp))
	{
		dead.push(temp);
		HealerCount--;
		KilledCount++;
		KilledHealer++;
		temp->SetStatus(KILD);
	}
	else if (freezers.dequeue(temp))
	{
		dead.push(temp);
		FreezerCount--;
		KilledCount++;
		KilledFreezer++;
		temp->SetStatus(KILD);
	}
	
	if (Frozen.dequeue(temp))   //killing one frozen
	{
		dead.push(temp);
		frozenCount--;
		KilledCount++;
		temp->SetStatus(KILD);
			if (dynamic_cast<const Fighter*>(temp))
			{
				FrostedFighter--;
			}
			else if (dynamic_cast<const Healer*>(temp))
			{
				FrostedHealer--;
			}
			else
			{
				FrostedFreezer--;
			}
	}



}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()	
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
	srand(time(0));
	for(int i=0; i<DemoListCount; i++)
	{
		pE = DemoList[i];
		switch(pE->GetStatus())
		{
		case ACTV:
			pE->Move();
			pE->Act();

			Prop = rand()%100;
			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST); 
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
					{
						pE->SetStatus(KILD);	
						ActiveCount--;
						KilledCount++;
					}
			
			break;
		case FRST:
			Prop = rand()%100;
			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
					{
						pE->SetStatus(KILD);	
						FrostedCount--;
						KilledCount++;
					}

			break;
		}
	}
}
