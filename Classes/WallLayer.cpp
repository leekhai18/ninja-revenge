#include "WallLayer.h"
#include "Global.h"

USING_NS_CC;

//WallLayer* WallLayer::instance = NULL;
//
//WallLayer* WallLayer::inst(){
//	//if (!instance){
//		instance = new WallLayer();
//		instance->init();
//	//}
//	return instance;
//}

Scene* WallLayer::createScene()
{
	// 'scene' is an autorelease object
	 scene = Scene::create();
	 scene->retain();
	// 'layer' is an autorelease object
	auto layer = WallLayer::create();
	layer->retain();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WallLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < N_WALL; i++){
		Sprite* wall = Sprite::create("wall layer\\wall.png");
		wall->setPosition(Point((i)*WALL_WIDTH, GROUND_HEIGHT + WALL_HEIGHT/2));
		wall->setTag(i);
		walls.push_back(wall);
		this->addChild(wall);
	}	

	for (int i = 0; i < N_GROUND; i++){
		Sprite* ground = Sprite::create("wall layer\\ground.png");
		ground->setPosition(Point((i)*GROUND_WIDTH, GROUND_HEIGHT/2));
		ground->setTag(i+ N_WALL);		
		grounds.push_back(ground);
		this->addChild(ground);
	}

	this->scheduleUpdate();

	return true;
}

void WallLayer::update(float delta){
	if (Global::isPause)
		return;

	for (auto &wall : walls){
		if (wall->getPosition().x < - WALL_WIDTH){
			int tag = wall->getTag() == 0 ? N_WALL - 1 : wall->getTag() - 1;
			wall->setPosition(Vec2(this->getChildByTag(abs(tag))->getPosition().x + WALL_WIDTH - (layerSpeed - 150)*delta,
				wall->getPosition().y));
		}
		else
			wall->setPosition(Vec2(wall->getPosition().x - (layerSpeed - 150)*delta, wall->getPosition().y));
	}
	
	for (auto &ground : grounds){
		if (ground->getPosition().x < - GROUND_WIDTH){
			int tag = ground->getTag() == N_WALL ? N_WALL + N_GROUND - 1 : ground->getTag() - 1;
			ground->setPosition(Vec2(this->getChildByTag(abs(tag))->getPosition().x + GROUND_WIDTH - layerSpeed*delta,
				ground->getPosition().y));
		}
		else
			ground->setPosition(Vec2(ground->getPosition().x - layerSpeed*delta, ground->getPosition().y));
	}
}

void WallLayer::resetWallPosition(cocos2d::Node* sender){
	sender->setPosition(Vec2(sender->getPosition().x + WALL_WIDTH * 6, sender->getPosition().y));
}
