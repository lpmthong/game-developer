#define GAME_HIGHT 600
#define GAME_WIDTH 800

#define BLUE 0

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//Quad tree
#define MAP_WIDTH 10000
#define MIN_NODE_WIDTH 25
#define NORMAL 0
#define LT 1
#define RT 2
#define RB 3
#define LB 4

//Object
#define BRICK 0
#define CLOUD 2
#define GRASS 3
#define FENCE 4
#define MUSHROOM_ENEMY 5
#define GROUND 6
#define GROUND_LEFT 7
#define GROUND_MIDDLE 8
#define GROUND_RIGHT 9
#define PLAYER_KID 10
#define PLAYER_ADULT 11
#define BRICK_BREAK 12
#define BRICK_BREAK_DISAPPEAR 13
//#define PIPE_CAP 14
//#define PIPE_BODY 15
#define BRICK_BONUS_MUSHROOM 16
#define BONUS_MUSHROOM 17
#define PLAYER_ADULT_GUN 18
#define BULLET 19
#define TURTLE 20
#define TURTLEDEATH 21
#define BRICK_BONUS_GUN 22
#define BRICK_BONUS_LIFE 23
#define BRICK_BONUS_COIN 24
#define OUTCOIN 25
#define HARDBRICK 26
#define PIRHANAPLANT 27
#define ENDMAP 28
#define MOUNTAIN 29
#define HIGHTREE 30
#define LOWTREE 31
#define CHECKPOINT 32
#define GROUND_SOIL 33
#define GROUND_SOIL_LEFT 34
#define GROUND_SOIL_RIGHT 35
#define GROUND_DARK_SOIL 36
#define CROSS 37
#define BRICK_BONUS_LIFE_HIDDEN 38
#define RED_TURTLE 39
#define RED_TURTLE_DEATH 40
#define GROUND_MUSHROOM_RIGHT 41
#define GROUND_MUSHROOM_MIDDLE 42
#define GROUND_MUSHROOM_LEFT 43

#define GROUNDUNDERMUSHROOM 45
#define BRICK_BONUS_STAR 46
#define PIPE_1 47
#define PIPE_2 48
#define PIPE_3 49
#define PIPE_4 50
#define PIPE_5 51
#define STATIC_CROSS 52
#define FALLING_CROSS 53


//Game State.
#define GS_MENU			0
#define GS_GAMEPLAY		1
#define GS_GAMEOVER		2
#define GS_OPTION		3
#define GS_CHANGEMAP	4
#define GS_GAMEOPTION	5	


//Menu
#define MENU_START		0
#define MENU_OPTION		1
#define MENU_EXIT		2

//GameOption
#define OPTION_CONTINUE	0
#define OPTION_NEWGAME	1
#define OPTION_SAVEGAME 2
#define OPTION_LOADGAME 3
#define OPTION_BACKMENU 4

//Death status
#define ALIVE 0
#define DYING 1
#define INHELL 2
#define DYING2 3

//Brick break type
#define BB_LEFT_TOP 0
#define BB_LEFT_BOTTOM 1
#define BB_RIGHT_TOP 2
#define BB_RIGHT_BOTTOM 3

//Bonus type
#define GROWUP 0
#define LIFE 1
#define GUN 2
#define COIN 3
#define STAR 4

//Collide direct
#define TOPLEFT		0
#define TOP			1
#define TOPRIGHT	2
#define RIGHT		3
#define BOTTOMRIGHT	4
#define BOTTOM		5
#define BOTTOMLEFT	6
#define LEFT		7
#define NONE		8

