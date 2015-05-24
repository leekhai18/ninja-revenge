#include "BackgroundLayer.h"

USING_NS_CC;
BackgroundLayer* BackgroundLayer::instance = NULL;

BackgroundLayer* BackgroundLayer::inst(){
	if (!instance){
		instance = new BackgroundLayer();
		instance->init();
	}
	return instance;
}

Scene* BackgroundLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BackgroundLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BackgroundLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	background = Sprite::create(BACKGROUND_1_PATH);
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2 + background->getContentSize().height/4);
	this->addChild(background);

	Sprite* house0 = Sprite::create(BG_HOUSE_2_PATH);
	house0->setPosition(house0->getContentSize().width / 2, GROUND_HEIGHT + WALL_HEIGHT);
	house0->setTag(0);
	house0->setScale(2.0f);
	houses.push_back(house0);
	this->addChild(house0);

	for (int i = 1; i < BG_N_HOUSE; i++){
		Sprite* house = Sprite::create(BG_HOUSE_1_PATH);
		int tag =  i - 1;
		house->setPosition(this->getChildByTag(tag)->getPosition().x + BG_HOUSE_1_WIDTH * 2,
			GROUND_HEIGHT + WALL_HEIGHT);
		house->setTag(i);
		house->setScale(2.0f);
		houses.push_back(house);
		this->addChild(house);

	}


	this->scheduleUpdate();

	return true;
}

void BackgroundLayer::update(float delta){
	for (Sprite* &house : houses){
		if (house->getPosition().x < -house->getContentSize().width){			
			int currentTag = house->getTag();
			this->removeChildByTag(currentTag);

			int rand = random(1, 2);			
			if (rand == 1){
				house = Sprite::create(BG_HOUSE_1_PATH);

			}
			else{
				house = Sprite::create(BG_HOUSE_2_PATH);
			}

			
			int tag = currentTag == 0 ? BG_N_HOUSE - 1 : currentTag - 1;
			//int pos = this->getChildByTag(tag)->getPosition().x;
			//int w = house->getContentSize().width;
			//int tmp = this->getChildByTag(tag)->getPosition().x + this->getChildByTag(tag)->getContentSize().width / 2 + house->getContentSize().width / 2 - HOUSE_SPEED*delta;
			house->setTag(currentTag);
			house->setScale(2.0f);
			house->setPosition(this->getChildByTag(tag)->getPosition().x + this->getChildByTag(tag)->getContentSize().width + house->getContentSize().width - layerSpeed*delta
				, GROUND_HEIGHT + WALL_HEIGHT);
			//houses.push_back(house);
			this->addChild(house);
		}
		else
			house->setPosition(house->getPosition().x - layerSpeed*delta, house->getPosition().y);
		

	}
	//if (rock->getPosition().x < -400){
	//	int rand = random(1, 2);

	//	if (rand == 1){
	//		rock = Sprite::create(ROCK_1_PATH);
	//		
	//	}
	//	else{
	//		rock = Sprite::create(ROCK_2_PATH);
	//	}
	//	rock->setPosition(random(1000, 1700), GROUND_HEIGHT + WALL_HEIGHT);
	//	this->addChild(rock);
	//}
	//else{
	//	rock->setPosition(rock->getPosition().x - delta*ROCK_SPEED, rock->getPosition().y);
	//}

}
