#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#define OMISLASH_PATH "UI\\omislash.png"
#define BLADE_STORM_PATH "UI\\bladeStorm.png"
#define SKILL_DISABLED_PATH "UI\\skillDisabled.png"


#include "cocos2d.h"
#include "Player.h"

class HUDLayer : public cocos2d::Layer
{
private:
	Player*			player;

	Size			visibleSize;
	bool			isTouchDown;
	Vec2			initTouchPos;
	Vec2			currentTouchPos;

	MenuItemImage* swordItem;
	MenuItemImage* omislashItem;
	MenuItemImage* bladeStormItem;
	CCRect *swordRect, *omiRect, *bladeRect;

public:
	static HUDLayer* create();

	virtual bool init() override;
	void update(float dt);

	void setPlayer(Player* _player) { player = _player; }
	// a selector callback
	void initSwordItem();
	void initBladeStormItem();
	void initOmiSlashItem();

	void slash(Ref* sender);
	void omislash(Ref* sender);
	void bladeStorm(Ref* sender);
	bool canJump(Vec2 touchPoint);
	bool intersect(CCRect* rect, Vec2 point);
};

#endif
