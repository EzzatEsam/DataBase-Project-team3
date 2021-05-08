#include "Battle.h"
#include "GUI\GUI.h"


//
#include <fstream>
#include <iostream>  //remove later
#include <sstream>

using namespace std;
int main()
{
	
	/*Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	
	delete pGameBattle;*/

	cout << "start debug" << endl;
	string FileName = "Text";

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
	std::cout << temp << endl;
	ss >> temp;    //assign castle atk number 
	std::cout << temp << endl;
	ss >> temp;   //assign castle atk damage 
	std::cout << temp << endl;
	getline(Myfile, Line);      //   second line and assign enemy 
	std::cout << Line << endl;
	while (Myfile >> Line)
	{
		cout << 's' << endl;
		cout << Line << endl;
	}
	

	
	return 0;
}
