#include "RockLayer.h"

USING_NS_CC;
//RockLayer* RockLayer::instance = NULL;
//
//RockLayer* RockLayer::inst(){
//	//if (!instance){
//		instance = new RockLayer();
//		instance->init();
//	//}
//	return instance;
//}

Scene* RockLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RockLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RockLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	rock = Sprite::create(ROCK_1_PATH);
	rock->setScale(2.0f);
	rock->setPosition(random(0, 700) + visibleSize.width, GROUND_HEIGHT + WALL_HEIGHT);
	this->addChild(rock);

	this->scheduleUpdate();

	return true;
}

void RockLayer::update(float delta){

	if (rock->getPosition().x < -400){
		this->removeChild(rock);

		int rand = random(1, 2);
		if (rand == 1){
			rock = Sprite::create(ROCK_1_PATH);
			
		}
		else{
			rock = Sprite::create(ROCK_2_PATH);
		}
		rock->setScale(2.0f);
		rock->setPosition(random(1000, 1700), GROUND_HEIGHT + WALL_HEIGHT);
		this->addChild(rock);
	}
	else{
		rock->setPosition(rock->getPosition().x - delta*layerSpeed, rock->getPosition().y);
	}

}
