#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define DEBUG_MODE 0

enum Z_ODER
{
	kBackGround = 0,
	kRock,
	kWall,
	kHouse,
	kBridge,
	kPlayerShadow,
	kEnemy,
	kPlayer,
	kHUD = 10
};

enum OBJECT_BISMASK
{
	PLAYER_MASK = 0x01,
	GROUND_MASK = 0x02,
	ENEMY_MASK = 0x03,
	KURENAI_MASK = 0x04,
	ARROW_MASK = 0x05,
	HOUSE_MASK = 0x06
};

enum OBJECT_TAG
{
	PLAYER_TAG = 1,
	GROUND_TAG,
	ENEMY_TAG,
	KURENAI_TAG,
	ARROW_TAG,
	HOUSE_TAG
};

enum ESTATE
{
	RUN = 0,
	JUMP,
	JUMP2,
	DIE,
	ATTACK,
	IDLE,
	SKILL1,
	SKILL2,
	SKILL3
};

enum ENEMY_TYPE
{
	ENEMY1,
	ENEMY2,
	ENEMY3
};

class Global
{
private:
	static Global*		instance;
	static bool			instanceFlag;

	Global() 
	{

	}

public:
	static bool isPause;
	//ctor & des
	~Global()
	{
		instanceFlag = false;
	}

	void init();
	Global* getInstance();

};

#endif