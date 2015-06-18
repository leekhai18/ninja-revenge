#ifndef _ENEMY_SPAWN_
#define _ENEMY_SPAWN_

#include "cocos2d.h"
#include "Global.h"
#include "Enemy.h"

USING_NS_CC;

class EnemySpawn : public Node
{
private:
	int			level;
	float		timer;
	float		timeToRespawn;

	Player*		player = nullptr;
	
	void caculateTimeToRespawn();
	void caculateEnemyType();

public:
	CC_SYNTHESIZE(float, minTime, MinTime);
	CC_SYNTHESIZE(float, maxTime, MaxTime);
	CC_SYNTHESIZE(int, maxEnemyType, MaxEnemyType);
	void setPlayer(Player* _player) { player = _player; }

	static EnemySpawn* createEnemySpawn();

	void update(float dt);

	void initSpawn();
	void setLevel(int lv);
	void levelUp();
	void respawn();
};

#endif