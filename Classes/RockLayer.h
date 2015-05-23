#ifndef __ROCK_LAYER_H__
#define __ROCK_LAYER_H__

#define ROCK_WIDTH 272
#define ROCK_HEIGHT 235
#define ROCK_SPEED 696.69f
#define ROCK_1_PATH "rock layer\\stone_1.png"
#define ROCK_2_PATH "rock layer\\stone_2.png"

#include "cocos2d.h"
#include "WallLayer.h"

class RockLayer : public cocos2d::Layer
{
private: 
	//std::vector<cocos2d::Sprite*> rocks;
	cocos2d::Sprite* rock;
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(RockLayer);
};

#endif 
