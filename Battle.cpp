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

Queue<string> Battle::Convert2Strings()
{

	Queue<string> Output_;
	string it = "Game is a ";
	it += (BCastle.GetHealth() > 0) ? "WIN" : "LOSE";
	Output_.enqueue(it);
	Output_.enqueue("KTS  ID    FD  KD  LT");
	Enemy *tempEnemy;
	int n = 0;
	float firstShotDelay = 0;
	float killDelay = 0;
	while (dead.dequeue(tempEnemy))
	{
		string Line = to_string(tempEnemy->GetDeathTime());
		Line += ReturnNChars(5 - Line.length()) + to_string(tempEnemy->GetID());
		Line += ReturnNChars(11 - Line.length()) + to_string(tempEnemy->GetFirstShotTime());
		Line += ReturnNChars(15 - Line.length()) + to_string(tempEnemy->GetDeathTime() - tempEnemy->GetFirstShotTime());
		Line += ReturnNChars(19 - Line.length()) + to_string(tempEnemy->GetDeathTime() - tempEnemy->GetArrvTime());
		Output_.enqueue(Line);
		killDelay += tempEnemy->GetDeathTime() - tempEnemy->GetFirstShotTime();
		firstShotDelay += tempEnemy->GetFirstShotTime() - tempEnemy->GetArrvTime();
		n++;
		auto test = tempEnemy->GetDeathTime();
		auto test2 = tempEnemy->GetFirstShotTime();
	}
	Output_.enqueue(ReturnNChars(22, '-'));
	Output_.enqueue(ReturnNChars(22, '-'));
	Output_.enqueue("Castle total damage :" +to_string(BCastle.castleTotalDamage));
	Output_.enqueue("Castle total taken damage :" + to_string(CastleStartHP- BCastle.castleTotalDamage));
	Output_.enqueue("Total enemies :"+to_string(EnemiesStartCount));
	Output_.enqueue("Total dead enemies :" + to_string(n));
	Output_.enqueue("Average first shot delay :" +to_string(firstShotDelay/(float)n)) ;
	Output_.enqueue("Average kill delay :" +to_string(killDelay/(float)n) );

	return Output_;
}

Castle *Battle::GetCastle()
{
	return &BCastle;
}

void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE
	mode = pGUI->getGUIMode();

	switch (mode) //Add a function for each mode in next phases
	{
	case MODE_INTR:
		InteractiveSimulation();
		break;
	case MODE_STEP:
		StepByStepSimulation();
		break;
	case MODE_SLNT:
		SilentSimulation();
		break;
	}
	FileManager mngr(this);
	pGUI->PrintMessage("Enter the output file name");
	mngr.WriteResult(Convert2Strings(),pGUI->GetString());
	delete pGUI;
}

void Battle::SetEnemyCount(int n)
{
	EnemyCount = n;
	EnemiesStartCount = n;
}

void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy *const *EnemyList = Q_Inactive.toArray(InactiveCount);
	std::cout << InactiveCount << endl;
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//
	int count;
	Enemy *const *fightersarr = Fighters.toArray(count);
	for (int i = 0; i < count; i++)
	{
		std::cout << "f" << endl;
		pGUI->AddToDrawingList(fightersarr[i]);
	}
	Enemy *const *healersarr = healers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(healersarr[i]);
		std::cout << "h" << endl;
	}
	Enemy *const *freezersarr = freezers.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(freezersarr[i]);
		std::cout << "fr" << endl;
	}
	Enemy *const *ded = dead.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(ded[i]);
		std::cout << "dd" << endl;
	}
	/*Enemy *const *frz = Frozen.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(frz[i]);
		std::cout << "fz" << endl;
	}*/
}

void Battle::InteractiveSimulation()
{
	FileManager mngr(this);
	pGUI->PrintMessage("Please enter file name");
here:
	try
	{
		auto out = mngr.GetInput(pGUI->GetString());
		Enemy *S;
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
	while (KilledCount < EnemyCount && BCastle.GetHealth() > 0)
	{
		CurrentTimeStep++;
		InitiateFight();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);
		pGUI->waitForClick();
	}
}

void Battle::StepByStepSimulation()
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

	Sleep(1000);

	//
	while (KilledCount < EnemyCount && BCastle.GetHealth() >0)
	{
		CurrentTimeStep++;
		InitiateFight();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.getFrozen(), FighterCount, HealerCount, FreezerCount, FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledHealer, KilledFreezer);

		Sleep(1000);
	}


}
void Battle::SilentSimulation()
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

	//
	while (KilledCount < EnemyCount && BCastle.GetHealth() >0)
	{
		CurrentTimeStep++;
		InitiateFight();

	}


}
void Battle::Action()
{
	// These Steps will occur each time step
	// 1) Move active enemies and let them act 
	int Fcount;
	Enemy *const *fightersarr = Fighters.toArray(Fcount);
	for (int i = 0; i < Fcount; i++)
	{
		Fighter *pF = dynamic_cast<Fighter *>(fightersarr[i]);
		if (pF->GetStatus() != FRST) {
			pF->Move();
		}
		pF->Act(GetCastle());
	}
	
	int Zcount;
	Enemy *const *freezersarr = freezers.toArray(Zcount);
	for (int i = 0; i < Zcount; i++)
	{
		Freezer *pZ = dynamic_cast<Freezer *>(freezersarr[i]);
		if (pZ->GetStatus() != FRST) {
			pZ->Move();
		}
		if (!GetCastle()->getFrozen()) {
			//A frosted castle is affected by fighter attacks only, and it can’t attack enemies.
			pZ->Act(GetCastle());
		}
		//cout << "Freezing Amount = " << GetCastle()->getFreezingAmount() << endl;
		//cout << "MAX Freezing Amount = " << GetCastle()->getMaxFreezeAmount() << endl;
	}

	int Hcount;
	Enemy* const* healersarr = healers.toArray(Hcount);
	for (int i = 0; i < Hcount; i++)
	{
		Healer* pH = dynamic_cast<Healer*>(healersarr[i]);
		if (pH->GetStatus() != FRST) {
			pH->Move();
		}
		for (int i = 0; i < Fcount; i++)
			pH->Act(fightersarr[i]);
		for (int i = 0; i < Zcount; i++)
			pH->Act(freezersarr[i]);
	}

	// 2) Handle Castle
	Castle *pC = GetCastle();

	// Generate no from 0 to 100
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 100);
	

	// If castle is frozen, defreeze and skip
	if (pC->getFrozen())
	{
		// Frozen
		if (pC->Freezing_Step == 0) {
			pC->setFrozen(false);
			pC->setFreezengAmount(0);
		}
		else {
			pC->Freezing_Step--;
		}
		cout << endl << "===============================" << endl << "This TS will not count" << endl << "===============================" << endl;
	}
	else
	{
		// Not frozen
		PriorityQueue<Enemy*> tmp_Fighters;
		Stack<Enemy*> tmp_Healres;
		Queue<Enemy*> tmp_Freezers;

		for (int i = 0; i <= (pC->getN() - 1); i++)
		{
			int random = dist(mt);
			bool snowBall = (random <= 20 ? true : false); // throw snow not fire

			Enemy* x;

			if (Fighters.RefreshThenDequeue(x))
			{ // Get all fighters and attack them
					tmp_Fighters.enqueue(x);
				if (!snowBall) {
					pC->Fire(x, CurrentTimeStep);
				}
				else
				{
					bool done = pC->Freeze(x, CurrentTimeStep);
					if (done)
					{
						Frozen.enqueue(x);
						FighterCount--;
						frozenCount++;
						FrostedFighter++;
					}
				}

				cout << "Fighter heal = " << x->getHealth() << endl;
			}
			else if (healers.pop(x))
			{ // no fighters, then get healers
					tmp_Healres.push(x);
				if (!snowBall) {
					pC->Fire(x, CurrentTimeStep);
				}
				else
				{
					bool done = pC->Freeze(x, CurrentTimeStep);
					if (done)
					{
						Frozen.enqueue(x);
						HealerCount--;
						frozenCount++;
						FrostedHealer++;
					}
				}
				cout << "Healer heal = " << x->getHealth() << endl;

			}
			else if (freezers.dequeue(x))
			{ // no healers, get freezers
					tmp_Freezers.enqueue(x);
				if (!snowBall) {
					pC->Fire(x, CurrentTimeStep);
				}
				else
				{
					bool done = pC->Freeze(x, CurrentTimeStep);
					if (done)
					{
						Frozen.enqueue(x);
						FreezerCount--;
						frozenCount++;
						FrostedFreezer++;
					}
				}
				cout << "Freezer heal = " << x->getHealth() << endl;
			}	

		}

		while (!tmp_Fighters.isEmpty()) {
			Enemy* x;
			tmp_Fighters.dequeue(x);
			Fighters.enqueue(x);
		}
		while (!tmp_Healres.isEmpty()) {
			Enemy* x;
			tmp_Healres.pop(x);
			healers.push(x);
		}
		while (!tmp_Freezers.isEmpty()) {
			Enemy* x;
			tmp_Freezers.dequeue(x);
			freezers.enqueue(x);
		}
	}

}

void Battle::DeFreeze() {
	Queue<Enemy*> tmp;
	while (!Frozen.isEmpty()) {
		Enemy* x;
		Frozen.dequeue(x);
		if (x->GetStatus() == FRST) {

		x->Frost_Time_Steps--;
		if (x->Frost_Time_Steps == 0) {
			// Not frosted anymore (dont put in the temp
			x->SetStatus(ACTV);
			Freezer* pZ = dynamic_cast<Freezer*>(x);
			Healer* pH = dynamic_cast<Healer*>(x);
			Fighter* pF = dynamic_cast<Fighter*>(x);
			if (pF) {
				//Fighters.enqueue(x);
				FighterCount++;
				FrostedFighter--;
			}
			if (pH) {
				//healers.push(x);
				HealerCount++;
				FrostedHealer--;
			}
			if (pZ) {
				//freezers.enqueue(x);
				FreezerCount++;
				FrostedFreezer--;
			}
		}
		else {
			tmp.enqueue(x);
		}
		}
	}


	while (!tmp.isEmpty()) {
		Enemy* x;
		tmp.dequeue(x);
		Frozen.enqueue(x);
	}
}

void Battle::Kill() {
	PriorityQueue<Enemy*> tmp_Fighters;
	Stack<Enemy*> tmp_Healres;
	Queue<Enemy*> tmp_Freezers;

	// Kill fighters
	while (!Fighters.isEmpty()) {
		Enemy* x;
		Fighters.dequeue(x);
		if (x->getHealth() <= 0) {
			// Dead
			dead.enqueue(x);
			FighterCount--;
			KilledCount++;
			KilledFighter++;
			x->SetStatus(KILD);
			x->DeathTime = CurrentTimeStep;
		}
		else {
			tmp_Fighters.enqueue(x);
		}
	}
	while (!tmp_Fighters.isEmpty()) {
		Enemy* x;
		tmp_Fighters.dequeue(x);
		Fighters.enqueue(x);
	}

	// Kill Healers
	while (!healers.isEmpty()) {
		Enemy* x;
		healers.pop(x);
		if (x->getHealth() <= 0) {
			// Dead
			// If Castle kills a healer within a distance of 5 meters from the castle, it uses healer's tools to recover its health by a percentage of 3%
			if (x->GetDistance() <= 5) {
				GetCastle()->SetHealth(GetCastle()->GetHealth() + GetCastle()->GetHealth() * 0.03);
			}
			dead.enqueue(x);
			HealerCount--;
			KilledCount++;
			KilledHealer++;
			x->SetStatus(KILD);
			x->DeathTime = CurrentTimeStep;
		}
		else {
			tmp_Healres.push(x);
		}
	}
	while (!tmp_Healres.isEmpty()) {
		Enemy* x;
		tmp_Healres.pop(x);
		healers.push(x);
	}

	// Kill Freezers
	while (!freezers.isEmpty()) {
		Enemy* x;
		freezers.dequeue(x);
		if (x->getHealth() <= 0) {
			// Dead
			dead.enqueue(x);
			FreezerCount--;
			KilledCount++;
			KilledFreezer++;
			x->SetStatus(KILD);
			x->DeathTime = CurrentTimeStep;
		}
		else {
			tmp_Freezers.enqueue(x);
		}
	}
	while (!tmp_Freezers.isEmpty()) {
		Enemy* x;
		tmp_Freezers.dequeue(x);
		freezers.enqueue(x);
	}
}

void Battle::CountAll() {
	int Fcount;
	Enemy* const* fightersarr = Fighters.toArray(Fcount);
	FighterCount = Fcount;

	int Zcount;
	Enemy* const* freezersarr = freezers.toArray(Zcount);
	FreezerCount = Zcount;

	int Hcount;
	Enemy* const* healersarr = healers.toArray(Hcount);
	HealerCount = Hcount;

	int FZcount;
	FrostedFighter = 0; FrostedHealer = 0; FrostedFreezer = 0;
	Enemy* const* frozenArr = Frozen.toArray(FZcount);
	for (int i = 0; i < FZcount; i++) {
		Freezer* pZ = dynamic_cast<Freezer*>(frozenArr[i]);
		Healer* pH = dynamic_cast<Healer*>(frozenArr[i]);
		Fighter* pF = dynamic_cast<Fighter*>(frozenArr[i]);
		if (pZ)
			FrostedFreezer++;
		if (pH)
			FrostedHealer++;
		if (pF)
			FrostedFighter++;
	}
}

void Battle::AddByType(Enemy *pE)
{
	if (dynamic_cast<const Fighter *>(pE))
	{
		Fighters.enqueue(pE);
		FighterCount++;
	}
	else if (dynamic_cast<const Healer *>(pE))
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
	while (Q_Inactive.peekFront(pE)) //as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep) //no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE); //remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddByType(pE);			//move it to the corrosponding ds
	}
}

//void Battle::UpdateEnemies()
//{
//
//	int count;
//	Enemy *const *fightersarr = Fighters.toArray(count);
//	for (int i = 0; i < count; i++)
//	{
//		fightersarr[i]->Move();
//		//fightersarr[i]->Act();
//	}
//	Enemy *const *healersarr = healers.toArray(count);
//	for (int i = 0; i < count; i++)
//	{
//		healersarr[i]->Move();
//		//healersarr[i]->Act();
//	}
//	Enemy *const *freezersarr = freezers.toArray(count);
//	for (int i = 0; i < count; i++)
//	{
//		freezersarr[i]->Move();
//		//freezersarr[i]->Act();
//	}
//	Enemy *temp;
//	//freezing two of each type
//	for (int i = 0; i < 2; i++)
//	{
//
//		if (Fighters.dequeue(temp))
//		{
//			FighterCount--;
//			frozenCount++;
//			Frozen.enqueue(temp);
//			temp->SetStatus(FRST);
//			FrostedFighter++;
//		}
//
//		if (healers.pop(temp))
//		{
//			HealerCount--;
//			frozenCount++;
//			Frozen.enqueue(temp);
//			temp->SetStatus(FRST);
//			FrostedHealer++;
//		}
//		if (freezers.dequeue(temp))
//		{
//			FreezerCount--;
//			frozenCount++;
//			Frozen.enqueue(temp);
//			temp->SetStatus(FRST);
//			FrostedFreezer++;
//		}
//	}
//
//	for (int i = 0; i < 2; i++) //defreezing 2
//
//	{
//		if (Frozen.dequeue(temp))
//		{
//			if (dynamic_cast<const Fighter *>(temp))
//			{
//				Fighters.enqueue(temp);
//				FighterCount++;
//				temp->SetStatus(ACTV);
//				FrostedFighter--;
//			}
//			else if (dynamic_cast<const Healer *>(temp))
//			{
//				healers.push(temp);
//				HealerCount++;
//				temp->SetStatus(ACTV);
//				FrostedHealer--;
//			}
//			else
//			{
//				freezers.enqueue(temp);
//				FreezerCount++;
//				temp->SetStatus(ACTV);
//				FrostedFreezer--;
//			}
//			frozenCount--;
//		}
//	}
//	if (Fighters.dequeue(temp)) //killing one fighter
//	{
//		
//		double val1 = temp->getPriority();
//		
//		dead.enqueue(temp);
//		FighterCount--;
//		KilledCount++;
//		KilledFighter++;
//		temp->SetStatus(KILD);
//	}
//	else if (healers.pop(temp))
//	{
//		dead.enqueue(temp);
//		HealerCount--;
//		KilledCount++;
//		KilledHealer++;
//		temp->SetStatus(KILD);
//	}
//	else if (freezers.dequeue(temp))
//	{
//		dead.enqueue(temp);
//		FreezerCount--;
//		KilledCount++;
//		KilledFreezer++;
//		temp->SetStatus(KILD);
//	}
//
//	if (Frozen.dequeue(temp)) //killing one frozen
//	{
//		dead.enqueue(temp);
//		frozenCount--;
//		KilledCount++;
//		temp->SetStatus(KILD);
//		if (dynamic_cast<const Fighter *>(temp))
//		{
//			FrostedFighter--;
//		}
//		else if (dynamic_cast<const Healer *>(temp))
//		{
//			FrostedHealer--;
//		}
//		else
//		{
//			FrostedFreezer--;
//		}
//	}
//}

void Battle::InitiateFight()
{
	ActivateEnemies();
	
	Action(); //the fight logic
	DeFreeze();
	Kill();
	CountAll();
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();
	
}

void Battle::SetCastleMaxHp(int n)
{
	BCastle.SetHealth(n);
	CastleStartHP = n;
	pGUI->SetMaxH(n);
}
