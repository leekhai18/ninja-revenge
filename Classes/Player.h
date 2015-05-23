#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

USING_NS_CC;
using namespace cocostudio;

enum ESTATE
{
	RUN = 0,
	JUMP,
	JUMP2,
	DIE,
	ATTACK
};

class Player : public Armature
{
private:
	//ESTATE		state;
	bool		isJumping;

public:
	//static create method
	static Player* create();

	//constructor & destroy
	Player();
	~Player();

	bool initPlayer();
	
	//override
	virtual void update(float dt);

	//get & set method || SYNTHESIZE
	CC_SYNTHESIZE(ESTATE, state, State);
	
	//behavior
	void run();
	void jump();
	void attack();
	void die();

	//event
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void addEvent();
};

#endif