#ifndef __BRIGDE_LAYER_H__
#define __BRIGDE_LAYER_H__

#define BRIGDE_FRONT_1_PATH "house layer\\bridge_front1.png"
#define BRIGDE_FRONT_1_HEIGHT 191

#include "cocos2d.h"
#include "WallLayer.h"
#include "BackgroundTemplate.h"

class BrigdeLayer : public BackgroundTemplate
{
private: 
	cocos2d::Sprite* brigde;
public:

	void addBrigde(float xLocation);

	cocos2d::Scene* createScene() override;
	virtual bool init() override;
	void update(float delta) override;
};

#endif 
