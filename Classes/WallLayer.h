#ifndef __WALL_LAYER_H__
#define __WALL_LAYER_H__

#define WALL_WIDTH 272
#define WALL_HEIGHT 235
#define WALL_SPEED 696.69f
#define N_WALL 6

#define GROUND_WIDTH 589
#define GROUND_HEIGHT 57
#define GROUND_SPEED 696.69
#define N_GROUND 6

#include "cocos2d.h"

class WallLayer : public cocos2d::Layer
{
private: 
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> grounds;
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	void resetWallPosition(cocos2d::Node* sender);
	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(WallLayer);
};

#endif 
