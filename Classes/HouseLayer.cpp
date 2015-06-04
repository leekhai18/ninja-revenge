#include "HouseLayer.h"

USING_NS_CC;
HouseLayer* HouseLayer::instance = NULL;

HouseLayer* HouseLayer::inst(){
	if (!instance){
		instance = new HouseLayer();
		instance->init();
	}
	return instance;
}


Scene* HouseLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HouseLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HouseLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int rand = random(1, 5);
	this->addHouse(rand);

	this->scheduleUpdate();

	return true;
}

void HouseLayer::update(float delta){
	if (house->getPosition().x < - house->getContentSize().width){
		this->addHouse(random(1, 5));
	}
	else{
		house->setPosition(house->getPosition().x - delta*layerSpeed, house->getPosition().y);
	}

}

void HouseLayer::addHouse(int rand){
	this->removeChild(house);
	rand = 0;
	int pos = random(0, 1000);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::string path;
	float diff, scaleFactor;

	//these diff only work when the scale factor is 2.0f
	switch (rand){
	case 0: {
				path = BRIGDE_BACK_1_PATH; diff = BRIGDE_BACK_1_HEIGHT / 2 - WALL_HEIGHT; scaleFactor = 1.0f;
				BrigdeLayer::inst()->addBrigde(pos + +visibleSize.width); break;
	}
				
	case 1: path = HOUSE_1_PATH; diff = 90; scaleFactor = SCALE_FACTOR;  break;
	case 2: path = HOUSE_2_PATH; diff = 90; scaleFactor = SCALE_FACTOR; break;
	case 3: path = HOUSE_3_PATH; diff = 50; scaleFactor = SCALE_FACTOR; break;
	case 4: path = HOUSE_4_PATH; diff = -20; scaleFactor = SCALE_FACTOR; break;
	case 5: path = HOUSE_5_PATH; diff = -20; scaleFactor = SCALE_FACTOR; break;
	}
	
	house = Sprite::create(path);
	
	//cocos2d::Vec2* points = new cocos2d::Vec2();
	//points->
	//b2Vec2 vertices[8];
	//vertices[0].Set(0, 10);
	//vertices[1].Set(0, 20);
	//vertices[2].Set(0, 30);
	//vertices[3].Set(0, 40);
	//vertices[4].Set(10, 0);
	//vertices[5].Set(20, 0);
	//vertices[6].Set(0, 70);
	//vertices[7].Set(0, 80);
	//if (rand == 0){
	//	auto body = PhysicsBody::createPolygon(vertices, PhysicsMaterial(1, 0, 0));
	//	body->setRotationEnable(false);
	//	body->setCollisionBitmask(5);
	//	body->setContactTestBitmask(true);
	//	body->setDynamic(false);
	//	house->setPhysicsBody(body);
	//}


	house->setScale(scaleFactor);
	house->setPosition(pos + visibleSize.width -500 +house->getContentSize().width / 2, WALL_HEIGHT + diff);
	this->addChild(house);
}