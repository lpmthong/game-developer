#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "SaveGame.h"
#include "GlobalHandler.h"
#include "Define.h"
#include "Ground.h"
#include "ListTexture.h"

SaveGame::SaveGame(void)
{
	__save_file = "Map\\Map0.txt";
}

SaveGame::~SaveGame(void)
{
}

void SaveGame::SetFile(char *file){
	__save_file = file;
}

void SaveGame::Save()
{
	SetFile("Map\\Map0.txt");
	ClearSaveFile();
	SaveMapInfo();
	GlobalHandler::SaveStaticObj();
	GlobalHandler::dynamicObjManager->Save();
	SavePlayerInfo();

	GlobalHandler::quadTree->Save();
}

void SaveGame::SaveMapInfo()
{
	SaveText(L"%d %d %d %d %d\n", GlobalHandler::mapWidth, GlobalHandler::mapLevel1, GlobalHandler::mapLevel2, GlobalHandler::backGroundColor, GlobalHandler::nextMap);
}

void SaveGame::SavePlayerInfo()
{
	SaveText(L"%d %d %d %d %d %d %d %d %d\n",
		GlobalHandler::player->id,
		GlobalHandler::player->isKind,
		GlobalHandler::player->rectDraw.left,
		GlobalHandler::player->rectDraw.top,
		GlobalHandler::player->lastCheckPoint, 
		GlobalHandler::player->life, 
		GlobalHandler::playerScore, 
		GlobalHandler::playerCoin, 
		GlobalHandler::time);
	
}

void SaveGame::SaveText( const LPWSTR format, ... )
{
	FILE *f = stderr;

	if (__save_file!=NULL)
	{
		if (fopen_s(&f, __save_file,"a")!=0) 
		{
			fprintf(stderr,"WARNING: Failed to open trace file '%s' for writing!\n",__save_file);
			return;
		}
	}

	va_list ap;
	va_start(ap,format);
	vfwprintf(f,format, ap);
	va_end(ap);

	//fprintf(f,"");

	if (__save_file!=NULL) fclose(f);
}


void SaveGame::ClearSaveFile()
{
	FILE *f = stderr;

	fopen_s(&f, __save_file,"w");
	fclose(f);
}

void SaveGame::SaveString(string input){

	ofstream myfile;
	myfile.open(__save_file, std::ofstream::out | std::ofstream::app);
	myfile << input;
	myfile.close();

}