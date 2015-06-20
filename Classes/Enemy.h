#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif
#include "Global.h"
#include "Player.h"

USING_NS_CC;
using namespace cocostudio;

#define ENEMY_SPEED 500

class Enemy : public Armature
{
private:
	bool		isAttacked = false;
	bool		isDie = false;
	bool		isOnGround = false;
	
	float		dictanceToSplash = 0;
	int			damage = 0;

	Size		visibleSize;

	Player*		player = nullptr;

public:
	//static create method
	static Enemy* create(ENEMY_TYPE _type);
	static int NUM_OF_ENEMY_KILLED;

	bool initEnemy(ENEMY_TYPE _type);

	//override
	virtual void update(float dt);

	//get & set method || SYNTHESIZE
	CC_SYNTHESIZE(ESTATE, state, State);
	CC_SYNTHESIZE(ENEMY_TYPE, enemyType, EnemyType);
	void setPlayer(Player* _player) { player = _player; }
	//behavior
	void idle();
	void attack();
	void setDie();

	//event
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	bool onContactBegin(PhysicsContact& contact);
};

#endif