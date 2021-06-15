#include "Battle.h"
#include <time.h>
#include "FileManager.h"
#include <iostream>
#include <random>
Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	//DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}

Queue<string> Battle::Convert2Strings()
{
	
	Queue<string> Output_;
	string it = "Game is a ";
	it += (BCastle.GetHealth() > 0) ? "WIN" : "LOSE";
	Output_.enqueue(it);
	Output_.enqueue("KTS  ID    FD  KD  LT");
	Enemy* tempEnemy;
	while (dead.dequeue(tempEnemy))
	{
		string Temp = to_string( tempEnemy->GetDeathTime()) + "    " +to_string( tempEnemy->GetID())  ;
		Temp += "           " +  to_string(tempEnemy->GetDeathTime() - tempEnemy->GetArrvTime()) ;
		Output_.enqueue(Temp);
	}




	return Output_;
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
		break;

	}
	FileManager mngr(this);
	mngr.WriteResult(Convert2Strings());
	delete pGUI;
	
}

void Battle::SetEnemyCount(int n)
	{
			EnemyCount = n;
	}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
//void Battle::Just_A_Demo()
//{	
//	
//	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
//	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//
//	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
//	pGUI->waitForClick();
//
//	CurrentTimeStep = 0;
//	//
//	// THIS IS JUST A DEMO Function
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	//
//	 
//	srand(time(NULL));
//	int Enemy_id = 0;
//	int ArrivalTime=1;
//	Enemy* pE= NULL;
//	//Create Random enemies and add them all to inactive queue
//	for(int i=0; i<EnemyCount; i++)
//	{			
//		ArrivalTime += (rand()%3);	//Randomize arrival time
//		//pE = new Enemy(++Enemy_id,ArrivalTime);
//		pE->SetStatus( INAC); //initiall all enemies are inactive
//		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
//	}	
//
//	AddAllListsToDrawingList();
//	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);	//upadte interface to show the initial case where all enemies are still inactive
//
//	pGUI->waitForClick();
//	
//	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
//	{
//		CurrentTimeStep++;
//		ActivateEnemies();
//
//		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
//
//		pGUI->ResetDrawingList();
//		AddAllListsToDrawingList();
//		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
//		Sleep(250);
//	}		
//}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	std::cout << InactiveCount << endl;
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
		auto out = mngr.GetInput(pGUI->GetString());
		Enemy* S;
		while (out.dequeue(S))
		{
			Q_Inactive.enqueue(S);
		}
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
	while (KilledCount < EnemyCount && BCastle.GetHealth() >0 )	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		//UpdateEnemies();
		Action(); //the fight logic
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		// following line is sh*t  change it !
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
		pGUI->waitForClick();
	}

}

void Battle::Action()
{
	// These Steps will occur each time step
	// 1) Move active enemies and let them act
	int Fcount;
	Enemy* const* fightersarr = Fighters.toArray(Fcount);
	for (int i = 0; i < Fcount; i++)
	{
		Fighter* pF = dynamic_cast<Fighter*>(fightersarr[i]);
		pF->Move();
		pF->Act(GetCastle());
	}
	int Hcount;
	Enemy* const* healersarr = healers.toArray(Hcount);
	for (int i = 0; i < Hcount; i++)
	{
		healersarr[i]->Move();
	}
	int Zcount;
	Enemy* const* freezersarr = freezers.toArray(Zcount);
	for (int i = 0; i < Zcount; i++)
	{
		Freezer* pZ = dynamic_cast<Freezer*>(freezersarr[i]);
		pZ->Move();
		pZ->Act(GetCastle());
		cout << "Freezing Amount = " << GetCastle()->getFreezingAmount() << endl;
		cout << "MAX Freezing Amount = " << GetCastle()->getMaxFreezeAmount() << endl;
	}

	// 2) Handle Castle
	Castle* pC = GetCastle();

	// Generate no from 0 to 100
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 100);
	int random = dist(mt);
	bool snowBall = (random <= 20 ? true : false); // throw snow not fire

	// If castle is frozen, defreeze and skip
	if (pC->getFrozen()) {
		// Frozen
		pC->setFrozen(false);
		pC->setFreezengAmount(0);
	}
	else {
		// Not frozen
		for (int i = 0; i <= (pC->getN() - 1); i++) {

			if (Fcount > i) { // Get all fighters and attack them 
				if (!snowBall)
					pC->Fire(fightersarr[i]);
				else {
					bool done = pC->Freeze(fightersarr[i]);
					if (done) {
					//Frozen.enqueue(fightersarr[i]);
					FighterCount--;
					frozenCount++;
					FrostedFighter++;
					}
				}
			}
			else if (Hcount > i - Fcount) { // no fighters, then get healers
				if (!snowBall)
					pC->Fire(healersarr[i - Fcount]);
				else {
					bool done = pC->Freeze(healersarr[i - Fcount]);
					if (done) {
						//Frozen.enqueue(healersarr[i - Fcount]);
						HealerCount--;
						frozenCount++;
						FrostedHealer++;
					}
				}
			}
			else if (Zcount > i - Fcount - Hcount) { // no healers, get freezers
				if (!snowBall)
					pC->Fire(freezersarr[i - Fcount - Hcount]);
				else {
					bool done = pC->Freeze(freezersarr[i - Fcount - Hcount]);
					if (done) {
						//Frozen.enqueue(healersarr[i - Fcount]);
						FreezerCount--;
						frozenCount++;
						FrostedFreezer++;
					}
				}
			}
		}
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
		if(pE->GetArrvTime() >  CurrentTimeStep )	//no more arrivals at current time
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
		dead.enqueue(temp);
		FighterCount--;
		KilledCount++;
		KilledFighter++;
		temp->SetStatus(KILD);
	}
	else if (healers.pop(temp))
	{
		dead.enqueue(temp);
		HealerCount--;
		KilledCount++;
		KilledHealer++;
		temp->SetStatus(KILD);
	}
	else if (freezers.dequeue(temp))
	{
		dead.enqueue(temp);
		FreezerCount--;
		KilledCount++;
		KilledFreezer++;
		temp->SetStatus(KILD);
	}
	
	if (Frozen.dequeue(temp))   //killing one frozen
	{
		dead.enqueue(temp);
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
//void Battle::Demo_UpdateEnemies()	
//{
//	Enemy* pE;
//	int Prop;
//	//Freeze, activate, and kill propablities (for sake of demo)
//	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
//	srand(time(0));
//	for(int i=0; i<DemoListCount; i++)
//	{
//		pE = DemoList[i];
//		switch(pE->GetStatus())
//		{
//		case ACTV:
//			pE->Move();
//			pE->Act();
//
//			Prop = rand()%100;
//			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
//			{
//				pE->SetStatus(FRST); 
//				ActiveCount--;
//				FrostedCount++;
//			}
//			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
//					{
//						pE->SetStatus(KILD);	
//						ActiveCount--;
//						KilledCount++;
//					}
//			
//			break;
//		case FRST:
//			Prop = rand()%100;
//			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
//			{
//				pE->SetStatus(ACTV);
//				ActiveCount++;
//				FrostedCount--;
//			}
//
//			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
//					{
//						pE->SetStatus(KILD);	
//						FrostedCount--;
//						KilledCount++;
//					}
//
//			break;
//		}
//	}
//}
