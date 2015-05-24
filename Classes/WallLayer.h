#ifndef __WALL_LAYER_H__
#define __WALL_LAYER_H__

#define WALL_WIDTH 272
#define WALL_HEIGHT 235
#define N_WALL 6

#define GROUND_WIDTH 589
#define GROUND_HEIGHT 57
#define N_GROUND 6

#include "cocos2d.h"
#include "BackgroundTemplate.h"
class WallLayer : public BackgroundTemplate
{
private: 
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> grounds;
	static WallLayer* instance;
public:

	static WallLayer* inst();

	cocos2d::Scene* createScene() override;
	bool init() override;
	void update(float delta) override;
	
	void resetWallPosition(cocos2d::Node* sender);
};

#endif 
