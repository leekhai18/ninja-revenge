#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

//#define ROCK_WIDTH 272
//#define ROCK_HEIGHT 235
//#define BG_HOUSE_SPEED 696.69f
#define BACKGROUND_1_PATH "background\\bg_2.png"

#define BG_HOUSE_2_PATH "background\\house_bg2.png"
#define BG_HOUSE_2_WIDTH 480
#define BG_HOUSE_2_HEIGHT "background\\house_bg1.png"

#define BG_HOUSE_1_PATH "background\\house_bg1.png"
#define BG_HOUSE_1_WIDTH 467
#define BG_HOUSE_1_HEIGHT "background\\house_bg1.png"

#define BG_N_HOUSE 4
#include "cocos2d.h"
#include "WallLayer.h"
#include "BackgroundTemplate.h"

class BackgroundLayer : public BackgroundTemplate
{
private: 
	std::vector<cocos2d::Sprite*> houses;
	cocos2d::Sprite* background;
public:
	cocos2d::Scene* createScene() override;
	bool init() override;
	void update(float delta) override;

	
};

#endif 
