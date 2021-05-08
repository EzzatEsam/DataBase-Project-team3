#include "FileManager.h"
#include <fstream>
#include <iostream>  //remove later
#include <sstream>
#include <string>
#include "Battle.h"


FileManager::FileManager(Battle* b)
{
	thisbattle = b;
}

Queue<Enemy*> FileManager::GetInput(string FileName)
{
	
	string folderName = ""; // modify
	string Line;
	ifstream Myfile(folderName + FileName + ".txt");
	if (!Myfile.is_open())
		throw;
	getline(Myfile, Line);  //first line
	stringstream ss(Line);
	string temp;
	//first line
	ss >> temp;  //assign castle hp  
	thisbattle->GetCastle()->SetHealth(stoi(temp));
	std::cout << temp << endl;
	ss >> temp;    //assign castle atk number 
	thisbattle->GetCastle()->SetAtkNum(stoi(temp));
	std::cout << temp << endl;
	ss >> temp;   //assign castle atk damage 
	thisbattle->GetCastle()->SetAtkDamage(stoi(temp));
	std::cout << temp << endl;
	getline(Myfile, Line);      //   second line and assign number enemy 
	std::cout << Line << endl;
	int EnemNo = stoi(Line);
	

	Queue<Enemy*> Out;
	for (int i = 0; i < EnemNo; i++)
	{
		getline(Myfile, Line);
		stringstream ss(Line);
		int id, type, TimeStep, hp, atk, relode, ms;
		ss >> temp;
		id = stoi(temp);
		ss >> temp;
		type = stoi(temp);
		ss >> temp;
		TimeStep = stoi(temp);
		ss >> temp;
		hp = stoi(temp);
		ss >> temp;
		atk = stoi(temp);
		ss >> temp;
		relode = stoi(temp);
		ss >> temp;
		ms = stoi(temp);

		Enemy* tempEnem = new Enemy(id, TimeStep);
		Out.enqueue(tempEnem);
	}
	return Out;
}

FileManager::~FileManager()
{
}

