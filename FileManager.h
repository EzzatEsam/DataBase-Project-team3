#pragma once
#include "Generic_DS\Queue.h"
#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Freezer.h"
#include "Enemies\Healer.h"
class Battle;
class FileManager
{
private:
	Battle* thisbattle;
public:
	FileManager(Battle*);
	Queue<Enemy*> GetInput(string FileName);
	void WriteResult(Queue<string> lines , string FileName = "Output");
	~FileManager();
};




