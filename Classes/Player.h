#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "Global.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

USING_NS_CC;
using namespace cocostudio;

#define	PLAYER_JUMP_SPEED		450
#define PLAYER_SLASH_DELAY		0.7f
#define PLAYER_TIME_HOLDING		0.3f
#define PLAYER_TIME_USE_SKILL1	10.0f
#define PLAYER_TIME_USE_SKILL2	10.0f
#define PLAYER_MAX_HP			500.0f
#define PLAYER_SKILL1_COOLDOWN	12
#define PLAYER_SKILL2_COOLDOWN	12

class Player : public Armature
{
private:
	Size		visisbleSize;
	bool		isJumping			= false;
	float		timeDelayAttack		= 0;
	bool		isHolding			= false;
	float		timeHolding			= 0;

	float		flashPositionY		= 0;
	bool		canFlash			= false;
	bool		isOnGround			= false;
	float		groundPosition		= 0;

	bool		canUseSkill1		= false;
	bool		isUsingSkill1		= false;
	float		timeToAddNewShadow	= 0;

	bool		canUseSkill2		= false;
	bool		isUsingSkill2		= false;

	//properties of player
	float		jumpSpeed;
	float		acttackSpeed;
	int			maxHitPoint;
	int			hitPoint			= 500;
	
	float		timeCoolDownSkill1	= 0;
	float		timeOfSkill1		= 0;

	float		timeCoolDownSkill2	= 0;
	float		timeOfSkill2		= 0;

public:
	//static create method
	static Player* create();

	//constructor & destroy
	Player();
	~Player();

	bool initPlayer();
	void loadPlayerData();
	
	//override
	virtual void update(float dt);

	//get & set method || SYNTHESIZE
	CC_SYNTHESIZE(ESTATE, state, State);

	//behavior
	void run();
	void jump();
	void setHold(bool val);

	void attack();
	void setDie();

	void flashUp();
	void flashDown();
	void setHit(int damage);

	//skill 1
	void addAShadow();
	void useOmislash();
	void useSkill1();
	bool getIsUseSkill1() { return isUsingSkill1; }

	//skill 2
	void useBladeStorm();
	bool getIsUseSkill2() { return isUsingSkill2; }

	void dirtPlay();

	bool canAttack();
	bool canOmiSlash();
	bool canBladeStorm();

	//event
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	bool onContactBegin(PhysicsContact& contact);
	void onContactSeperate(PhysicsContact& contact);

	void destroyCallback(Node* node);

	int getHP();
	int getMaxHP();
};

#endif