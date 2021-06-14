#pragma once
#include <iostream>
#include <string>
using namespace std;

static string ReturnNChars(int n, char c = ' ')
{
	string S = "";
	for (int i = 0; i < n; i++)
	{
		S += c;
	}
	return S;
}