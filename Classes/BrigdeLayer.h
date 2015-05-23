#ifndef __BRIGDE_LAYER_H__
#define __BRIGDE_LAYER_H__


#define BRIGDE_FRONT_1_PATH "house layer\\bridge_front1.png"
#define BRIGDE_FRONT_1_HEIGHT 191
#define BRIGDE_SPEED 696.69f

#include "cocos2d.h"
#include "WallLayer.h"

class BrigdeLayer : public cocos2d::Layer
{
private: 
	cocos2d::Sprite* brigde;
	cocos2d::Scene* scene;
	static BrigdeLayer* instance;
public:

	static BrigdeLayer* inst();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	cocos2d::Scene* createScene();

	void addBrigde(float xLocation);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	void update(float delta);

	// implement the "static create()" method manually
	//CREATE_FUNC(BrigdeLayer);
};

#endif 
