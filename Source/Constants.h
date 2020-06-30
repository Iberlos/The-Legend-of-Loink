#pragma once

#include <GameDev2D.h>


//Tile constants
const float TILE_SIZE = 64.0f;
const int NUM_ROWS = 11;
const int NUM_COLUMNS = 16;
const int NUM_TILES = NUM_ROWS * NUM_COLUMNS;

//Region constants
const int NUM_REGION_ROWS = 3;
const int NUM_REGION_COLUMNS = 3;
const int NUM_REGIONS = NUM_REGION_ROWS * NUM_REGION_COLUMNS + 3;
const GameDev2D::Vector2 REGION_SIZE = GameDev2D::Vector2(NUM_COLUMNS * TILE_SIZE, NUM_ROWS * TILE_SIZE);

//Camera constants
const double CAMERA_TRANSITION_DURATION = 0.8;

//Link constants
const GameDev2D::Vector2 LINK_INITIAL_POSITION = GameDev2D::Vector2(1504.0f, 352.0f);
const double LINK_ATTACK_DURATION = 0.2;
const float LINK_SPEED = 250.0f;
const unsigned int NUMBER_OF_LINK_DIRECTIONS = 4;
const GameDev2D::Vector2 LINK_DIRECTIONS[] = { GameDev2D::Vector2::Left, GameDev2D::Vector2::Right, GameDev2D::Vector2::Up, GameDev2D::Vector2::Down };

const float LINK_ATTACK_RADIUS = 24.0f;
const int LINK_INITIAL_HEALTH = 6;

const std::pair<GameDev2D::Vector2, GameDev2D::Vector2> LINK_COLISION_OFFSETS[] = {
	std::make_pair(GameDev2D::Vector2(-28.0f,0.0f),GameDev2D::Vector2(-28.0f, -28.0f)),  //left
	std::make_pair(GameDev2D::Vector2(28.0f,0.0f),GameDev2D::Vector2(28.0f, -28.0f)),    //right
	std::make_pair(GameDev2D::Vector2(-16.0f,0.0f),GameDev2D::Vector2(16.0f, 0.0f)),     //up
	std::make_pair(GameDev2D::Vector2(-16.0f,-28.0f),GameDev2D::Vector2(16.0f, -28.0f))};//down

//Link Direction Enum
enum LinkDirection
{
    LinkLeft = 0,
    LinkRight,
    LinkUp,
    LinkDown
};

//Debug Draw enum
enum DebugDrawState
{
    DebugDraw_Empty = 0,
    DebugDraw_Indices,
    DebugDraw_Coordinates,
    DebugDraw_Count,
    DebugDraw_Nothing = -1
};

//Game State enum
enum GameState
{
    StateLoading = 0,
    StateGame,
	StateCave
};

//Load Step enum
enum LoadStep
{
	LoadTextures = 0,  //0
	LoadLink,          //1
	LoadDebugDrawing,  //2
	LoadSoundFiles,    //3
	LoadRegion0_0,     //4
	LoadRegion0_1,	   //5
	LoadRegion0_2,     //6
	LoadRegion1_0,     //7
	LoadRegion1_1,     //8
	LoadRegion1_2,     //9
	LoadRegion1_3,     //10
	LoadRegion1_4,     //11
	LoadRegion1_5,     //12
	LoadRegion2_0,     //13
	LoadRegion2_1,     //14
	LoadRegion2_2,     //15
	LoadHUD,           //16
	LoadCave,		   //17
	LoadFinalize,	   //18

	//Add additional load steps here

	LoadStepCount      //16
};


enum TileType
{
	TileType_Ground = 0,	//(0000 0000 0000 0000)
	TileType_Water = 1,		//(0000 0000 0000 0001)
	TileType_Sand = 2,		//(0000 0000 0000 0010)
	TileType_Rock = 3,		//(0000 0000 0000 0011)
	TileType_Boulder = 4,	//(0000 0000 0000 0100)
	TileType_Tree = 5,		//(0000 0000 0000 0101)
	TileType_Cave = 6,		//(0000 0000 0000 0110)
	TileType_Waterfall = 7, //(0000 0000 0000 0111)
	TileType_Bridge = 8,	//(0000 0000 0000 1000)
	TileType_Stairs = 9,    //(0000 0000 0000 1001)
	TileType_Ladder = 10,	//(0000 0000 0000 1010)
	TileType_EvilTree = 11,	//(0000 0000 0000 1011)
	TileType_Dungeon = 12,	//(0000 0000 0000 1100)
	TileType_Desert = 13,	//(0000 0000 0000 1101)
	TileType_Special = 14,	//(0000 0000 0000 1110)
	TileType_Unused = 15	//(0000 0000 0000 1111) - May come in handy later
};

enum TileVariant
{
	TileVariant_0 = 0,		//(0000 0000 0000 0000) center
	TileVariant_1 = 16,		//(0000 0000 0001 0000) top left
	TileVariant_2 = 32,		//(0000 0000 0010 0000) top
	TileVariant_3 = 48,		//(0000 0000 0011 0000) top right
	TileVariant_4 = 64,		//(0000 0000 0100 0000) right
	TileVariant_5 = 80,		//(0000 0000 0101 0000) lower right
	TileVariant_6 = 96,		//(0000 0000 0110 0000) down
	TileVariant_7 = 112,	//(0000 0000 0111 0000) lower left
	TileVariant_8 = 128,	//(0000 0000 1000 0000) left
	TileVariant_9 = 144,	//(0000 0000 1001 0000)
	TileVariant_10 = 160,	//(0000 0000 1010 0000)
	TileVariant_11 = 176,	//(0000 0000 1011 0000)
	TileVariant_12 = 192	//(0000 0000 1100 0000)
};

enum TileColor
{
	TileColor_Primary = 0,     //(0000 0000 0000 0000)
	TileColor_Secondary = 256, //(0000 0001 0000 0000)
	TileColor_Tertiary = 512   //(0000 0010 0000 0000)
};


const unsigned short LEVEL_0_0[] = {	1, 1, 19,19,19,19,19, 19,19,19,19,19,0, 0, 19,19,
										1, 1, 19,19,19,19,19, 4,19,19,19,67,0, 0, 19,19,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,19,
										1, 65, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 51,19,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 51,
										1, 65, 0, 4, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 35,
										1, 65, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 35,19,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,19,
										1, 1,  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 19,19,
										1, 1,  19,19,19,19,19,19,19,19,19,19,19,19,19, 19 };

const unsigned short LEVEL_0_1[] = {	19,19,19,19,19,19,19,0,0,19,19,19,19,19,19,19,
										19,19,19,19,6,19,67,0,0,19,19,19,19,19,19,19,
										19,19,19,67,0,0,0,0,0,19,19,19,19,19,19,19,
										19,19,67,0,0,0,0,0,0,19,19,19,19,19,19,19,
										19,67,0,0,0,0,0,0,0,51,19,19,19,19,19,19,
										0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
										3,83,0,0,0,0,0,0,0,0,0,0,0,0,3,3,
										19,19,0,0,0,0,0,0,0,0,0,0,0,0,19,19,
										19,19,0,0,0,0,0,0,0,0,0,0,0,0,19,19,
										19,19,3,3,3,3,3,3,3,3,3,3,3,3,19,19,
										19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19 };

//Level 0-2
const unsigned short LEVEL_0_2[] = {	19,19,5,0,5,0,5,129,65,261,2,261,2,261,2,19,
										19,19,5,0,5,0,5,129,65,261,2,261,2,261,2,19,
										19,19,0,0,0,0,0,129,65,2,2,2,2,2,2,19,
										19,67,0,0,0,0,5,129,65,261,2,261,2,261,2,19,
										67, 0,5,0,5,0,0,129,65,2,2,2,2,2,2,19,
										0,  0,0,0,0,0,5,129,65,261,2,261,2,261,2,19,
										83, 0,5,0,5,0,0,129,65,2,2,2,2,2,2,19,
										19,83,0,0,0,0,5,129,65,261,2,261,2,261,2,19,
										19,19,0,0,0,0,0,129,65,2,2,2,2,2,2,51,
										19,19,5,5,5,5,5,129,65,261,261,261,261,261,261,261,
										19,19,5,5,5,5,5,129,65,261,261,261,261,261,261,261 };

//Level 1-0
const unsigned short LEVEL_1_0[] = {	1, 65, 0, 0, 0, 0,19,19,19,19,19,19,19,19,19,19,
										1, 65, 0, 0, 0, 0,51,19,19,4,19,19,19,19,19,19,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,51,19,
										1, 65, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0,0,51,
										1, 65, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0,0,
										1, 65, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0,
										1, 65, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 35,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35,19,
										1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,83, 0, 0, 19,19,
										1, 1,19,19,19,19,19,19,19,19,19,19, 0, 0, 19,19 };

//Level 1-1
const unsigned short LEVEL_1_1[] = {	19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
										19,19,19,19,19,19,19, 6,19,19,19,19,19,19,19,19,
										19,67, 0, 0, 0, 0, 0, 0, 0,51,67, 0, 0, 0,19,19,
										67,0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 51,19,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51,
										0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										83, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 35,
										19,83, 0, 0, 0, 0, 0, 0, 0, 35,83,0, 0, 0, 35,19,
										19,19, 3, 3, 3, 3, 3, 0, 0, 19,19, 3, 3, 3,19,19,
										19,19,19,19,19,19,19, 0, 0, 19,19,19,19,19,19,19 };

//Level 1-2
const unsigned short LEVEL_1_2[] = {	19,19,19,19,19,19,19,7,7,19,19,19,19,19,19,19,
										19,19,5,51,19,67,0,129,65,261,51,19,67,261,51,67,
										19,19,0,0,19,0,0,8,8,2,2,19,2,2,2,2,
										19,67,0,0,51,10,3,7,7,3,10,67,2,2,2,2,
										67,0,0,0,0,0,0,129,65,2,2,2,2,2,2,2,
										0,0,0,0,0,0,0,129,65,2,2,2,2,2,2,261,
										0,0,0,0,0,0,0,129,65,2,2,2,2,2,2,2,
										83,0,0,0,5,0,0,129,65,2,261,2,2,2,2,2,
										19,83,0,0,0,0,0,129,65,2,2,2,2,2,2,2,
										19,19,5,0,5,0,5,129,65,261,2,261,2,261,2,35,
										19,19,5,0,5,0,5,129,65,261,2,261,2,261,2,19 };

//Level 2-0
const unsigned short LEVEL_2_0[] = {	1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,
										1, 1, 97,8,97,97,97,97,97,97,97,97,97,97,97,97,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,0,
										1, 65, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0, 0,35,83, 0, 0, 0, 0, 0, 0, 0,
										1, 65, 0, 0, 0, 0,35,19,19, 3, 3, 3, 83, 0, 0, 0,
										1, 65, 0, 0, 0, 0,19,19,19,19,19,19, 19, 3, 3,3 };

//Level 2-1
const unsigned short LEVEL_2_1[] = {	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										97, 97, 97, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										0, 5, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										0, 5, 0, 129, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										0, 5, 0, 129, 1,1,1,1,1, 1, 1, 1, 1, 1, 1, 1,
										3,3,3,1,1,1,1,1,1,1, 1, 1, 1, 1, 1, 1 };

//Level 2-2
const unsigned short LEVEL_2_2[] = {	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										1, 1, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 1,
										1, 1, 275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 275, 1,
										1, 1, 275, 0, 11, 59, 0, 11, 43, 59, 0, 11, 59, 0, 275, 1,

										1, 1, 275, 0, 27, 75, 0, 27, 6, 75, 0, 27, 75, 0, 275, 1,
										8, 8, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 275, 1,
										1, 1, 275, 0, 0, 11, 59, 0, 0, 0, 11, 59, 0, 0, 275, 1,

										1, 1, 275, 0, 0, 27, 75, 0, 0, 0, 27, 75, 0, 0, 275, 1,
										1, 1, 275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 275, 1,
										1, 1, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 1,
										1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//Level 1-2
const unsigned short LEVEL_1_3[] = { 
	19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
	2,2,51,67,2,2,51,67,2,2,51,67,2,2,51,67,
	2,2,261,2,2,2,261,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,261,2,2,2,261,2,2,2,2,261,2,2,
	2,261,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,261,2,2,2,2,261,2,2,2,2,2,2,2,
	2,35,83,2,2,35,83,2,2,35,83,2,2,35,83,2,
	3,19,19,3,3,19,19,3,3,19,19,3,3,19,19,3, };

//Level 1-2
const unsigned short LEVEL_1_4[] = { 
	19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
	2,2,51,67,2,2,51,67,2,2,51,67,2,2,51,67,
	2,2,2,2,2,2,2,261,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,261,2,2,
	2,2,261,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,261,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,35,83,2,2,35,83,2,2,35,83,2,2,35,83,2,
	3,19,19,3,3,19,19,3,3,19,19,3,3,19,19,3, };

//Level 1-2
const unsigned short LEVEL_1_5[] = { 
	19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
	2,2,51,67,2,261,51,67,2,2,51,67,2,2,51,19,
	2,2,2,2,261,2,2,2,2,2,2,261,2,2,2,19,
	2,2,2,2,2,2,267,299,315,2,2,2,2,2,2,19,
	2,2,2,2,2,2,283,6,331,2,2,2,261,2,2,19,
	2,261,2,2,2,2,2,2,2,261,2,2,2,2,2,19,
	2,2,2,2,261,2,2,2,2,2,2,2,2,2,2,19,
	2,2,2,2,2,2,2,2,261,2,2,2,2,2,35,19,
	2,35,83,2,2,35,83,2,2,35,83,2,2,35,19,19,
	3,19,19,3,3,19,19,3,3,19,19,3,3,19,19,19,
	19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,   //Can`t figure out why does this level need an extra line of tiles!
};

//Cave
const unsigned short CAVE[] = { 22,22,22,22,22,22,22,22,  22,22,22,22,22,22,22,22,
								22,22,22,22,22,22,22,22,  22,22,22,22,22,22,22,22,
								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,
								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,

								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,
								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,
								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,

								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,
								22,22,6,6,6,6,6,6,  6,6,6,6,6,6,22,22,
								22,22,22,22,22,22,22,6,  6,22,22,22,22,22,22,22,
								22,22,22,22,22,22,22,6,  6,22,22,22,22,22,22,22 };


enum PickupType
{
	PickupType_WoodSword = 0,
	PickupType_Bombs,
	PickupType_OldLetter,
	PickupType_Candle,
	PickupType_Bracelet,
	PickupType_Triforce
};

enum CaveType
{
	CaveType_WoodSword = 0,
	CaveType_Bombs,
	CaveType_OldLetter,
	CaveType_Choose,
	CaveType_ETGreen,
	CaveType_ETRed,

	CaveType_Count
};

enum EnemyType
{
	Enemy_Fire = 0
};

enum SoundType
{
	Theme_Sound = 0,
	DungeonTheme_Sound,
	Item_Sound,
	Secret_Sound,
	Sword_Sound,
	BombDrop_Sound,
	BombExplosion_Sound,
	Hurt_Sound,
	LowHealth_Sound,
	Fire_Sound,
	LinkDeath_Sound,


	ALL_SOUND_EFFECTS
};