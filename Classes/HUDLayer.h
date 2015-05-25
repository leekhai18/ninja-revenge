#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "Player.h"

class HUDLayer : public cocos2d::Layer
{
private:
	Player* player;
public:
	static HUDLayer* create();

	virtual bool init() override;
	void setPlayer(Player* _player) { player = _player; }
	// a selector callback
	void slash(Ref* sender);
};

#endif
