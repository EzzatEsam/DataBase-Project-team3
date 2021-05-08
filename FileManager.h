#pragma once
#include "Generic_DS\Queue.h"
#include "Enemies\Enemy.h"
#include "Battle.h"
class FileManager
{
public:
	FileManager(Battle* b) { thisbattle = b; };
	Queue<Enemy*> GetInput(string FileName);
	~FileManager() {};
private:
	Battle *thisbattle;
};




