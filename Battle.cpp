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
	
	CurrentTimeStep = 0;
	pGUI = NULL;
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
		string Line = to_string(tempEnemy->GetDeathTime());
		Line += ReturnNChars(5-Line.length()) +to_string( tempEnemy->GetID());
		Line += ReturnNChars(11 - Line.length()) + to_string(tempEnemy->GetFirstShotTime());
		Line += ReturnNChars(15 - Line.length()) + to_string(tempEnemy->GetDeathTime() - tempEnemy->GetFirstShotTime());
		Line += ReturnNChars(19 - Line.length()) + to_string(tempEnemy->GetDeathTime() - tempEnemy->GetArrvTime()) ;
		Output_.enqueue(Line);
	}
	Output_.enqueue(ReturnNChars(22, '-'));
	Output_.enqueue(ReturnNChars(22, '-'));
	Output_.enqueue("Castle total damage :");
	Output_.enqueue("Total enemies :");
	Output_.enqueue("Average first shot delay :");
	Output_.enqueue("Average kill delay :");



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

	}
	FileManager mngr(this);
	mngr.WriteResult(Convert2Strings());
	delete pGUI;
	
}

void Battle::SetEnemyCount(int n)
	{
			EnemyCount = n;
	}



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
	while (KilledCount < EnemyCount && BCastle.GetHealth() >0 )	
	{
		CurrentTimeStep++;
		InitiateFight();
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

void Battle::InitiateFight()
{
	ActivateEnemies();
	UpdateEnemies();
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();
	// following line is sh*t  change it !
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
}

void Battle::SetCastleMaxHp(int n)
{
	BCastle.SetHealth(n);
	pGUI->SetMaxH(n);
}


