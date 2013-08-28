#include "ListTerrain.h"
#include "Brick.h"
#include "Define.h"
#include "Cloud.h"
#include "Grass.h"
#include "fence.h"
#include "MushroomEnemy.h"
#include "Ground.h"
#include "Player.h"
#include "BrickBreak.h"
#include "Pipe.h"
#include "BonusBrick.h"
#include "BonusMushroom.h"
#include "Bullet.h"
#include "TurleEnemy.h"
#include "Text.h"
#include "Coin.h"
#include "HardBrick.h"
#include "PirhanaPlant.h"
#include "EndMap.h"
#include "Mountain.h"
#include "HighTree.h"
#include "LowTree.h"
#include "Cross.h"
#include "RedTurleEnemy.h"
#include "GroundMushRoom.h"
#include "FallingCross.h"
#include "GroundUnderMushroom.h"

int ListTerrain::arr_terrain[10000];
int ListTerrain::arr_terrain_index = 0;

ListTerrain::ListTerrain(void)
{
}

ListTerrain::~ListTerrain(void)
{
}

void ListTerrain::Render()
{
	
}

void ListTerrain::InitTerrain(int level)
{
	ListTerrain::arr_terrain_index = 0;
	GlobalHandler::checkpoint_index = 0;
	ListTerrain::LoadFile(level);

	//Two first number in the file present for map Level.
	GlobalHandler::mapLevel1 = arr_terrain[0];
	GlobalHandler::mapLevel2 = arr_terrain[1];

	GlobalHandler::backGroundColor = arr_terrain[2];

	for (int i = 3; i < arr_terrain_index; i+=3)
	{
		if (arr_terrain[i] == BRICK)
		{
			Brick* brick = new Brick(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(brick);
		}
		else if (arr_terrain[i] == CLOUD)
		{
			Cloud* cloud = new Cloud(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(cloud);
		}
		else if (arr_terrain[i] == GRASS)
		{
			Grass* grass = new Grass(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(grass);
		}
		else if (arr_terrain[i] == FENCE)
		{
			Fence* fence = new Fence(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(fence);
		}
		else if (arr_terrain[i] == MUSHROOM_ENEMY)
		{
			MushroomEnemy* mushroomEnemy = new MushroomEnemy(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(mushroomEnemy);
		}
		else if (arr_terrain[i] == GROUND_LEFT || arr_terrain[i] == GROUND_MIDDLE || arr_terrain[i] == GROUND_RIGHT || arr_terrain[i] == GROUND_SOIL || arr_terrain[i] == GROUND_SOIL_LEFT || arr_terrain[i] == GROUND_SOIL_RIGHT || arr_terrain[i] == GROUND_DARK_SOIL)
		{
			Ground* ground = new Ground(arr_terrain[i+1], arr_terrain[i+2]);
			ground->setType(arr_terrain[i]);
			GlobalHandler::quadTree->AddNode(ground);
		}
		else if (arr_terrain[i] == GROUND_MUSHROOM_LEFT || arr_terrain[i] == GROUND_MUSHROOM_MIDDLE || arr_terrain[i] == GROUND_MUSHROOM_RIGHT)
		{
			GroundMushRoom* groundMushRoom = new GroundMushRoom(arr_terrain[i+1], arr_terrain[i+2]);
			groundMushRoom->setType(arr_terrain[i]);
			GlobalHandler::quadTree->AddNode(groundMushRoom);
		}
		else if (arr_terrain[i] == PLAYER_KID || arr_terrain[i] == PLAYER_ADULT || arr_terrain[i] == PLAYER_ADULT_GUN)
		{
			GlobalHandler::player->Init(arr_terrain[i], arr_terrain[i+1], arr_terrain[i+2]);
			
			GlobalHandler::playerScore = arr_terrain[i + 3];
			GlobalHandler::playerCoin = arr_terrain[i + 4];
			GlobalHandler::levelTime = arr_terrain[i + 5];
			GlobalHandler::mapLevel = arr_terrain[i + 6];
			i += 4;
			
			GlobalHandler::dynamicObjManager->Add(GlobalHandler::player);
		}
		else if (arr_terrain[i] == BRICK_BREAK)
		{
			BrickBreak* brickBreak = new BrickBreak(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(brickBreak);
		}
		else if (arr_terrain[i] == PIPE_CAP || arr_terrain[i] == PIPE_BODY)
		{
			Pipe* pipe = new Pipe(arr_terrain[i+1], arr_terrain[i+2], arr_terrain[i]);
			GlobalHandler::quadTree->AddNode(pipe);
		}
		else if (arr_terrain[i] == BRICK_BONUS_MUSHROOM || arr_terrain[i] == BRICK_BONUS_GUN || arr_terrain[i] == BRICK_BONUS_LIFE || arr_terrain[i] == BRICK_BONUS_COIN || arr_terrain[i] == BRICK_BONUS_LIFE_HIDDEN)
		{
			if (arr_terrain[i] == BRICK_BONUS_LIFE_HIDDEN)
				int a = 2;
			BonusBrick* bonusBrick = new BonusBrick(arr_terrain[i+1], arr_terrain[i+2]);
			bonusBrick->setType(arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(bonusBrick);
		}
		else if (arr_terrain[i] == BONUS_MUSHROOM)
		{
			BonusMushroom* bonusMushroom = new BonusMushroom(arr_terrain[i+1], arr_terrain[i+2]);
			bonusMushroom->setBonusType(GROWUP);
			GlobalHandler::dynamicObjManager->Add(bonusMushroom);
		}
		else if (arr_terrain[i] == BULLET)
		{
			Bullet* bullet = new Bullet(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(bullet);
		}
		else if (arr_terrain[i] == TURLE)
		{
			TurleEnemy* turle = new TurleEnemy(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(turle);
		}
		else if (arr_terrain[i] == OUTCOIN)
		{
			Coin* coin = new Coin(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(coin);
		}
		else if (arr_terrain[i] == HARDBRICK)
		{
			HardBrick* hardBrick = new HardBrick(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(hardBrick);
		}
		else if (arr_terrain[i] == PIRHANAPLANT)
		{
			PirhanaPlant* pirhana = new PirhanaPlant(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(pirhana);
		}
		else if (arr_terrain[i] == ENDMAP)
		{
			EndMap* endMap = new EndMap(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(endMap);
		}
		else if (arr_terrain[i] == MOUNTAIN)
		{
			Mountain* mountain = new Mountain(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(mountain);
		}
		else if (arr_terrain[i] == HIGHTREE)
		{
			HighTree* highTree = new HighTree(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(highTree);
		}
		else if (arr_terrain[i] == LOWTREE)
		{
			LowTree* lowTree = new LowTree(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(lowTree);
		}
		else if (arr_terrain[i] == CHECKPOINT)
		{
			GlobalHandler::checkpoint[0][GlobalHandler::checkpoint_index] = arr_terrain[i+1];
			GlobalHandler::checkpoint[1][GlobalHandler::checkpoint_index] = arr_terrain[i+2];
			GlobalHandler::checkpoint_index++;
		}
		else if (arr_terrain[i] == CROSS)
		{
			Cross* cross = new Cross(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(cross);
		}
		else if (arr_terrain[i] == RED_TURLE)
		{
			RedTurleEnemy* redTurle = new RedTurleEnemy(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(redTurle);
		}
		else if (arr_terrain[i] == FALLING_CROSS)
		{
			FallingCross* fallingCross = new FallingCross(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::dynamicObjManager->Add(fallingCross);
		}
		else if (arr_terrain[i] == GROUNDUNDERMUSHROOM)
		{
			GroundUnderMushroom* grdUnderMushroom = new GroundUnderMushroom(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(grdUnderMushroom);
		}
		else if (arr_terrain[i] == BRICK_BONUS_STAR)
		{
			BonusBrick* bonusBrick = new BonusBrick(arr_terrain[i+1], arr_terrain[i+2]);
			bonusBrick->setType(arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(bonusBrick);
		}
	}
}

void ListTerrain::LoadFile( int level )
{
	//Define map:
	//first number and second number for map level.
	//Each next 3 number for object type, object left and object top.
	CHAR filePath[50];
	sprintf_s(filePath,"Map\\Map%d.txt",level);

	string str = ReadFile(filePath);

	char stemp[4];
	int stemp_index = 0;
	for (int i =0;i<str.length();i++)
	{
		if (str[i] != 32 && i != str.length() - 1)
			if (stemp_index < 4)
			{
				stemp[stemp_index++] = str[i];
			}
			else
			{}
		else
		{
			arr_terrain[arr_terrain_index ++] = atoi(stemp);

			stemp[0] = ' ';
			stemp[1] = ' ';
			stemp[2] = ' ';
			stemp[3] = ' ';
			stemp_index = 0;
		}
	}
}

string ListTerrain::ReadFile( char* name )
{
	FILE *ffile;
	char ch;
	string st="";
	ffile=fopen(name,"rb");

	while(!feof(ffile)){
		ch=fgetc(ffile);
		st+=ch;
	}

	fclose(ffile);
	return st;
}
