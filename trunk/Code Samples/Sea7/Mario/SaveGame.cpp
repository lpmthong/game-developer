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

char *__save_file = "Map\\Map0.txt";

SaveGame::SaveGame(void)
{
}

SaveGame::~SaveGame(void)
{
}

void SaveGame::Save()
{
	ClearSaveFile();
	SaveMapInfo();
	GlobalHandler::quadTree->SaveFile();
	GlobalHandler::dynamicObjManager->SaveFile();
	SavePlayerInfo();
}

void SaveGame::SaveObject( Object* obj )
{
//	count++;
	if (obj->iKind == GROUND)
	{
		Ground* grd = (Ground*)obj;
		SaveText(L" %d %d %d", grd->type, obj->recDrawArea.left, obj->recDrawArea.top);
	}
	else if (obj->iKind == ENDMAP)
		SaveText(L" %d %d %d", obj->iKind, obj->recDrawArea.left, obj->recDrawArea.top + ListTexture::TT_END_MAP_HEIGHT - 31);
	else
		SaveText(L" %d %d %d", obj->iKind, obj->recDrawArea.left, obj->recDrawArea.top);
}

void SaveGame::SaveMapInfo()
{
	SaveText(L"%d %d %d", GlobalHandler::mapLevel1, GlobalHandler::mapLevel, GlobalHandler::backGroundColor);
}

void SaveGame::SavePlayerInfo()
{
	SaveText(L" %d %d %d %d %d %d %d",GlobalHandler::player->iKind, 
		GlobalHandler::player->lastCheckPoint, 
		GlobalHandler::player->life, 
		GlobalHandler::playerScore, 
		GlobalHandler::playerCoin, 
		GlobalHandler::levelTime,
		GlobalHandler::mapLevel);
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

	fprintf(f,"\n");

	if (__save_file!=NULL) fclose(f);
}

void SaveGame::ClearSaveFile()
{
	FILE *f = stderr;

	fopen_s(&f, __save_file,"w");
	fclose(f);
}