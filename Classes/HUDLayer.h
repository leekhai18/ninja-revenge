#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

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
public:
	static HUDLayer* create();

	virtual bool init() override;
	void update(float dt);

	void setPlayer(Player* _player) { player = _player; }
	// a selector callback
	void slash(Ref* sender);
};

#endif
