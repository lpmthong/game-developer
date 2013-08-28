#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Object.h"

class SaveGame
{
//	ofstream Students;
	int count;
public:
	SaveGame(void);
	~SaveGame(void);

	void Save();
	void SaveObject(Object* obj);
	void SaveMapInfo();
	void SavePlayerInfo();

	void SaveText(const LPWSTR format, ...);

	void ClearSaveFile();
};
