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

	GlobalHandler::backGroundColor = arr_terrain[3];
	for (int i = 4; i < arr_terrain_index ; i += 3)
	{		
		if (arr_terrain[i] == CLOUD)
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
		else if (arr_terrain[i] == GROUND_LEFT || arr_terrain[i] == GROUND_MIDDLE || arr_terrain[i] == GROUND_RIGHT || arr_terrain[i] == GROUND_SOIL || arr_terrain[i] == GROUND_SOIL_LEFT || arr_terrain[i] == GROUND_SOIL_RIGHT || arr_terrain[i] == GROUND_DARK_SOIL)
		{
			Ground* ground = new Ground(arr_terrain[i+1], arr_terrain[i+2]);
			ground->setType(arr_terrain[i]);
			GlobalHandler::quadTree->AddNode(ground);
		}
		else if (arr_terrain[i] == PIPE_CAP || arr_terrain[i] == PIPE_BODY)
		{
			Pipe* pipe = new Pipe(arr_terrain[i+1], arr_terrain[i+2], arr_terrain[i]);
			GlobalHandler::quadTree->AddNode(pipe);
		}
		else if (arr_terrain[i] == OUTCOIN)
		{
			Coin* coin = new Coin(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(coin);
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
		else if (arr_terrain[i] == CHECKPOINT )
		{
			GlobalHandler::checkpoint[0][GlobalHandler::checkpoint_index] = arr_terrain[i+1];
			GlobalHandler::checkpoint[1][GlobalHandler::checkpoint_index] = arr_terrain[i+2];
			GlobalHandler::checkpoint_index++;
		}
		else if (arr_terrain[i] == HARDBRICK)
		{
			HardBrick *hardbrick = new HardBrick(arr_terrain[i+1], arr_terrain[i+2]);
			GlobalHandler::quadTree->AddNode(hardbrick);
		}
	}

}