#ifndef _EnumPlantType_H_
#define _EnumPlantType_H_

enum PlantType
{
	en_PeaShooter = 1,
	en_CherryBomb,
	en_ScaredyShroom,
	en_IcePea,
	en_SunFlower,
	en_Threepeater,
	en_WallNut
};

enum PlantState
{
	en_PlantAtEase = 1,
	en_PlantAttacking,
	en_PlantDead
};

enum ZombieType
{
	en_NormalZombie = 1,
	en_BucketheadZombie,
	en_ConeheadZombie,
	en_FlagZombie
};

enum ZombieState
{
	en_ZombieMoving = 1,
	en_ZombieStopped,
	en_ZombieAttacking,
	en_ZombieDead
};

enum GameState
{
	en_GameWin = 1,
	en_GameLose,
	en_GameTied
};

enum StateInSpace
{
	en_Floating,
	en_InShield
};

#endif