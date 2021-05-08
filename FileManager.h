#pragma once
#include "Generic_DS\Queue.h"
#include "Enemies\Enemy.h"
class Battle;
class FileManager
{
private:
	Battle* thisbattle;
public:
	FileManager(Battle*);
	Queue<Enemy*> GetInput(string FileName);
	~FileManager();
};




