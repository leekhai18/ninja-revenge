#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(HUDLayer);
};

#endif
