#pragma once
#include <list>
#include "StaticObject.h"
using namespace std;

class ListTerrain
{
private:
	static int arr_terrain[10000];
	static int arr_terrain_index;
public:
	ListTerrain(void);

	//Init all terrain in map
	static void InitTerrain(int level);

	//load content of a file to a array 
	static void LoadFile(int level);

	//put content of a file to a string 
	static string ReadFile(char* name);

	void Render();
	~ListTerrain(void);
};
