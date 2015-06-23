#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#define SKILL1_PATH "UI\\i_skill1.png"
#define OMISLASH_PATH "UI\\omislash.png"
#define BLADE_STORM_PATH "UI\\bladeStorm.png"
#define SKILL_DISABLED_PATH "UI\\skillDisabled.png"

#define HP_BAR_PATH "UI\\hpBar.png"
#define HP_BAR_BORDER_PATH "UI\\hpBarBorder.png"

#define HEAD_PATH "UI\\head.png"
#define HEAD_ANGRY_PATH "UI\\head_angry.png"
#define HEAD_DIE_PATH "UI\\outch.png"
#define HP_DECREASE_DURATION 500.0f
#define DELTA_TIME 1000.0f/60.0f


#include "cocos2d.h"
#include "Player.h"
#include "Background.h"
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

	Sprite *hpBarBorder, *headIcon;
	CCProgressTimer *hpBar;

	Label* lbDistance;
	Label* lbGold;
	Label* lbCombo;

	Sprite* sprHit;
	Sprite* sprHits;
public:
	static HUDLayer* create();

	virtual bool init() override;
	void update(float dt);

	void setPlayer(Player* _player) { player = _player; }
	// a selector callback
	void initSwordItem();
	void initBladeStormItem();
	void initOmiSlashItem();

	float tmpHP;
	float hpDecRate;
	void initHpBar();
	void updateHpBar();

	void slash(Ref* sender);
	void omislash(Ref* sender);
	void bladeStorm(Ref* sender);
	bool canJump(Vec2 touchPoint);
	bool intersect(CCRect* rect, Vec2 point);
};

#endif
