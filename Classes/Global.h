#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//define some config (don't use too much)
#define DEBUG_MODE 1

enum OBJECT_BISMASK
{
	PLAYER_MASK = 0x01,
	GROUND_MASK = 0x02,
	ENEMY_MASK = 0x03,
	KURENAI_MASK = 0x04,
	ARROW_MASK = 0x05
};

enum OBJECT_TAG
{
	PLAYER_TAG = 1,
	GROUND_TAG,
	ENEMY_TAG,
	KURENAI_TAG,
	ARROW_TAG
};

enum ESTATE
{
	RUN = 0,
	JUMP,
	JUMP2,
	DIE,
	ATTACK,
	IDLE
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
	//ctor & des
	~Global()
	{
		instanceFlag = false;
	}

	void init();
	Global* getInstance();

};

#endif