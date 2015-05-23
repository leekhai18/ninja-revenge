#ifndef __HOUSE_LAYER_H__
#define __HOUSE_LAYER_H__

//#define ROCK_WIDTH 272
//#define ROCK_HEIGHT 235
#define SCALE_FACTOR 2.0f
#define HOUSE_SPEED 696.69f
#define HOUSE_1_PATH "house layer\\house_1.png"
#define HOUSE_2_PATH "house layer\\house_2.png"
#define HOUSE_3_PATH "house layer\\house_3.png"
#define HOUSE_4_PATH "house layer\\house_4.png"
#define HOUSE_5_PATH "house layer\\house_5.png"

#define BRIGDE_BACK_1_PATH "house layer\\bridge_back1.png"
#define BRIGDE_BACK_1_HEIGHT 199



#include "cocos2d.h"
#include "WallLayer.h"
#include "BrigdeLayer.h"

class HouseLayer : public cocos2d::Layer
{
private: 
	//std::vector<cocos2d::Sprite*> rocks;
	cocos2d::Sprite* house;

	void addHouse(int rand);
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(HouseLayer);
};

#endif 
