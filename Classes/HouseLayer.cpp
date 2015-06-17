#include "HouseLayer.h"
#include "Global.h"

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

Node* HouseLayer::createOneWayNode(float width, float height)
{
	Node* node = Node::create();
	auto body = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0, 0, 0));
	body->setRotationEnable(false);
	body->setDynamic(false);
	body->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	body->setContactTestBitmask(true);
	node->setPhysicsBody(body);
	node->setName("Ground");
	node->setTag(OBJECT_TAG::GROUND_TAG);
	return node;
}

void HouseLayer::update(float delta){
	if (house->getPosition().x < - house->getContentSize().width - random(100, 1000)){
		this->addHouse(random(1, 5));
	}
	else{
		house->setPosition(house->getPosition().x - delta*layerSpeed, house->getPosition().y);
	}

}

void HouseLayer::addHouse(int rand){
	this->removeChild(house);
	int pos = random(300, 1000);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::string path;
	float diff, scaleFactor;
	
	Node* child1;
	Node* child2;

	switch (rand){
	case 0: {
				path = BRIGDE_BACK_1_PATH; diff = BRIGDE_BACK_1_HEIGHT / 2 - WALL_HEIGHT; scaleFactor = 1.0f;
				BrigdeLayer::inst()->addBrigde(pos + visibleSize.width); 
				house = Sprite::create(path);
				break;
	}
				
	case 1: 
		path = HOUSE_1_PATH; diff = 90; scaleFactor = SCALE_FACTOR;
		house = Sprite::create(path);
		child1 = createOneWayNode(house->boundingBox().size.width * 0.6f, visibleSize.height * 0.02f);
		child1->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.77);
		child2 = createOneWayNode(house->boundingBox().size.width * 0.69f, visibleSize.height * 0.02f);
		child2->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.4);
		house->addChild(child1);
		house->addChild(child2);
		break;
	case 2: 
		path = HOUSE_2_PATH; diff = 90; scaleFactor = SCALE_FACTOR; 
		house = Sprite::create(path);
		child1 = createOneWayNode(house->boundingBox().size.width * 0.6f, visibleSize.height * 0.02f);
		child1->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.75);
		
		house->addChild(child1);
		break;
	case 3: 
		path = HOUSE_3_PATH; diff = 50; scaleFactor = SCALE_FACTOR; 
		house = Sprite::create(path);
		child1 = createOneWayNode(house->boundingBox().size.width * 0.6f, visibleSize.height * 0.02f);
		child1->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.7);

		house->addChild(child1);
		break;
	case 4: 
		path = HOUSE_4_PATH; diff = -20; scaleFactor = SCALE_FACTOR; 
		house = Sprite::create(path);
		child1 = createOneWayNode(house->boundingBox().size.width * 0.6f, visibleSize.height * 0.02f);
		child1->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.7);

		house->addChild(child1);
		break;
	case 5: 
		path = HOUSE_5_PATH; diff = -20; scaleFactor = SCALE_FACTOR; 
		house = Sprite::create(path);
		child1 = createOneWayNode(house->boundingBox().size.width * 0.6f, visibleSize.height * 0.02f);
		child1->setPosition(house->boundingBox().size.width * 0.5f, house->boundingBox().size.height * 0.7);

		house->addChild(child1);
		break;
	}

	auto houseBody = PhysicsBody::createBox(house->boundingBox().size, PhysicsMaterial(0, 0, 0));
	houseBody->setRotationEnable(false);
	houseBody->setDynamic(false);
	houseBody->setCollisionBitmask(OBJECT_BISMASK::HOUSE_MASK);
	houseBody->setContactTestBitmask(true);
	house->setPhysicsBody(houseBody);
	house->setName("House");
	house->setTag(OBJECT_TAG::HOUSE_TAG);
	

	house->setScale(scaleFactor);
	house->setPosition(pos + visibleSize.width, WALL_HEIGHT + diff);
	this->addChild(house);
}