#include "GlobalHandler.h"
#include "ListTerrain.h"
#include "Define.h"
#include "Cloud.h"
#include "Grass.h"
#include "Fence.h"
#include "Ground.h"
#include "Pipe.h"
#include "Coin.h"
#include "Mountain.h"
#include "HighTree.h"
#include "LowTree.h"
#include "HardBrick.h"
#include "Brick.h"
#include "BonusBrick.h"
#include "MushroomEnemy.h"
#include "TurtleEnemy.h"
#include "PirhanaPlant.h"
#include "Cross.h"
#include "GroundMushRoom.h"
#include "GroundUnderMushRoom.h"

int ListTerrain::arr_terrain[10000];
int ListTerrain::arr_terrain_index = 0;

ListTerrain::ListTerrain(void)
{
}

ListTerrain::~ListTerrain(void)
{
}

void ListTerrain::LoadFile(int level){

	char filePath[50];
	sprintf_s(filePath,"Map\\Map%d.txt",level);

	ifstream file;

	file.open(filePath);

	if(!file.is_open()){
		trace(L"Khong doc duoc file Map");
		exit(EXIT_FAILURE);
	}

	char word[100];
	
	while(file.good()){		
		file >> word;
		arr_terrain[arr_terrain_index] = atoi(word);
		arr_terrain_index++;
	}
	
	file.close();
}

void ListTerrain::InitTerrain(int level){
		

	ListTerrain::arr_terrain_index = 0;
	
	ListTerrain::LoadFile(level);

	

	GlobalHandler::quadTree = new QuadTree(arr_terrain[0], arr_terrain[0]);		
	GlobalHandler::mapLevel1 = arr_terrain[1];
	GlobalHandler::mapLevel2 = arr_terrain[2];
	GlobalHandler::backGroundColor = arr_terrain[3];
	for (int i = 4; i < arr_terrain_index ; i += 4)
	{		
		if (arr_terrain[i+1] == CLOUD)
		{
			Cloud* cloud = new Cloud(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(cloud);
		}
		else if (arr_terrain[i+1] == GRASS)
		{
			Grass* grass = new Grass(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(grass);
		}
		else if (arr_terrain[i+1] == FENCE)
		{
			Fence* fence = new Fence(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(fence);
		}
		else if (arr_terrain[i+1] == GROUND_LEFT || arr_terrain[i+1] == GROUND_MIDDLE || arr_terrain[i+1] == GROUND_RIGHT || 
					arr_terrain[i+1] == GROUND_SOIL || arr_terrain[i+1] == GROUND_SOIL_LEFT || arr_terrain[i+1] == GROUND_SOIL_RIGHT ||
						arr_terrain[i+1] == GROUND_DARK_SOIL)
		{
			Ground* ground = new Ground(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			ground->setType(arr_terrain[i+1]);
			GlobalHandler::listStaticObj.push_back(ground);
		}
		else if (arr_terrain[i+1] == PIPE_1 || arr_terrain[i+1] == PIPE_2 || arr_terrain[i+1] == PIPE_3)
		{
			Pipe* pipe = new Pipe(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i+1], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(pipe);
		}
		else if (arr_terrain[i+1] == OUTCOIN)
		{
			Coin* coin = new Coin(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(coin);
		}		
		else if (arr_terrain[i+1] == MOUNTAIN)
		{
			Mountain* mountain = new Mountain(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(mountain);
		}
		else if (arr_terrain[i+1] == HIGHTREE)
		{
			HighTree* highTree = new HighTree(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(highTree);
		}
		else if (arr_terrain[i+1] == LOWTREE)
		{
			LowTree* lowTree = new LowTree(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(lowTree);
		}
		else if (arr_terrain[i+1] == CHECKPOINT )
		{
			GlobalHandler::checkpoint[0][GlobalHandler::checkpoint_index] = arr_terrain[i+2];
			GlobalHandler::checkpoint[1][GlobalHandler::checkpoint_index] = arr_terrain[i+3];
			GlobalHandler::checkpoint_index++;
		}
		else if (arr_terrain[i+1] == HARDBRICK)
		{
			HardBrick *hardbrick = new HardBrick(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(hardbrick);
		} 
		else if (arr_terrain[i+1] == BRICK)
		{
			Brick *brick = new Brick(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::listStaticObj.push_back(brick);
		}
		else if (arr_terrain[i+1] == BRICK_BONUS_MUSHROOM || arr_terrain[i+1] == BRICK_BONUS_GUN || 
					arr_terrain[i+1] == BRICK_BONUS_LIFE || arr_terrain[i+1] == BRICK_BONUS_COIN || 
						arr_terrain[i+1] == BRICK_BONUS_LIFE_HIDDEN || arr_terrain[i+1] == BRICK_BONUS_STAR)
		{
			BonusBrick *bonusBrick = new BonusBrick(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i+4], arr_terrain[i]);	
			bonusBrick->setType(arr_terrain[i+1]);
			GlobalHandler::listStaticObj.push_back(bonusBrick);
			i += 1;
		}
		else if(arr_terrain[i+1] == MUSHROOM_ENEMY)
		{
			MushroomEnemy *mushroomEnemy = new MushroomEnemy(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(mushroomEnemy);
		}
		else if(arr_terrain[i+1] == TURTLE)
		{
			TurtleEnemy *turtleEnemy = new TurtleEnemy(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(turtleEnemy);
		}
		else if(arr_terrain[i+1] == PIRHANAPLANT)
		{
			PirhanaPlant *pirhanaPlant = new PirhanaPlant(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(pirhanaPlant);
		}
		else if(arr_terrain[i+1] == CROSS)
		{
			Cross *cross = new Cross(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			GlobalHandler::dynamicObjManager->Add(cross);
		}
		else if(arr_terrain[i+1] == GROUND_MUSHROOM_LEFT || arr_terrain[i+1] == GROUND_MUSHROOM_MIDDLE || arr_terrain[i+1] == GROUND_MUSHROOM_RIGHT)
		{
			GroundMushRoom *groundMushRoom = new GroundMushRoom(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);
			groundMushRoom->setType(arr_terrain[i+1]);
			GlobalHandler::listStaticObj.push_back(groundMushRoom);
		}
		else if(arr_terrain[i+1] == GROUNDUNDERMUSHROOM)
		{
			GroundUnderMushroom *groundUnderMushRoom = new GroundUnderMushroom(arr_terrain[i+2], arr_terrain[i+3], arr_terrain[i]);			
			GlobalHandler::listStaticObj.push_back(groundUnderMushRoom);
		}
		
	}

}