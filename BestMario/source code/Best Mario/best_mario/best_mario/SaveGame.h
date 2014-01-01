#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class SaveGame
{
	//	ofstream Students;
private:
	char *__save_file;
	
public:
	SaveGame(void);
	~SaveGame(void);

	void SetFile(char *file);
	void Save();	
	void SaveMapInfo();
	void SavePlayerInfo();

	void SaveText(const LPWSTR format, ...);
	void SaveString(string input);

	void ClearSaveFile();
};
