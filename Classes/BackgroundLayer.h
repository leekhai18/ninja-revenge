#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

//#define ROCK_WIDTH 272
//#define ROCK_HEIGHT 235
//#define ROCK_SPEED 696.69f
#define BACKGROUND_1_PATH "background\\bg_2.png"

#define HOUSE_2_PATH "background\\house_bg2.png"
#define HOUSE_1_WIDTH 480
#define HOUSE_1_HEIGHT "background\\house_bg1.png"

#define HOUSE_1_PATH "background\\house_bg1.png"
#define HOUSE_1_WIDTH 467
#define HOUSE_1_HEIGHT "background\\house_bg1.png"

#define HOUSE_SPEED 699
#define N_HOUSE 4
#include "cocos2d.h"
#include "WallLayer.h"

class BackgroundLayer : public cocos2d::Layer
{
private: 
	std::vector<cocos2d::Sprite*> houses;
	cocos2d::Sprite* background;
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(BackgroundLayer);
};

#endif 
