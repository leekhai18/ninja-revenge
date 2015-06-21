#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#define BACKGROUND_SPEED	200.69f
#define GROUND_SPEED		500

#include "cocos2d.h"
#include "WallLayer.h"
#include "BackgroundLayer.h"
#include "HouseLayer.h"
#include "BrigdeLayer.h"
#include "RockLayer.h"
class Background
{
private: 
	WallLayer* wallLayer;
	BackgroundLayer* backgroundLayer;
	HouseLayer* houseLayer;
	BrigdeLayer* brigdeLayer;
	RockLayer* rockLayer;
	static Background* instance;
	
public:
	static Background* inst();
	static float SPEED_UP;

	BackgroundLayer* createBackground();
	HouseLayer* createHouse();
	RockLayer* createRock();
	WallLayer* createWall();
	BrigdeLayer* createBrigde();

	void setSpeed(float percent);	
};

#endif 
