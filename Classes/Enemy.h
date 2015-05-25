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

USING_NS_CC;
using namespace cocostudio;


class Enemy : public Armature
{
private:

public:
	//static create method
	static Enemy* create(ENEMY_TYPE _type);

	bool initEnemy(ENEMY_TYPE _type);

	//override
	virtual void update(float dt);

	//get & set method || SYNTHESIZE
	CC_SYNTHESIZE(ESTATE, state, State);
	CC_SYNTHESIZE(ENEMY_TYPE, enemyType, EnemyType);
	//behavior
	void idle();
	void attack();
	void die();

	//event
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	bool onContactBegin(PhysicsContact& contact);
};

#endif