#ifndef __ROCK_LAYER_H__
#define __ROCK_LAYER_H__


#define ROCK_1_PATH "rock layer\\stone_1.png"
#define ROCK_2_PATH "rock layer\\stone_2.png"

#include "cocos2d.h"
#include "WallLayer.h"
#include "BackgroundTemplate.h"
class RockLayer : public BackgroundTemplate
{
private: 
	cocos2d::Sprite* rock;
	static RockLayer* instance;
public:
	static RockLayer* inst();

	cocos2d::Scene* createScene() override;
	bool init() override;
	void update(float delta) override;
};

#endif 
