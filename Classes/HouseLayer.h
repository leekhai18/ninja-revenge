#ifndef __HOUSE_LAYER_H__
#define __HOUSE_LAYER_H__

#define SCALE_FACTOR 2.0f

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
#include "BackgroundTemplate.h"
#include "Box2D\Box2D.h"
class HouseLayer : public BackgroundTemplate
{
private: 
	//std::vector<cocos2d::Sprite*> rocks;
	cocos2d::Sprite* house;
	void addHouse(int rand);

	Node* createOneWayNode(float width, float height);
	
public:

	cocos2d::Scene* createScene() override;
	bool init() override;
	void update(float delta) override;
};

#endif 
