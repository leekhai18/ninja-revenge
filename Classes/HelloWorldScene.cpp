#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	if (DEBUG_MODE)
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto ground = PhysicsBody::createBox(Size(960, 10), PhysicsMaterial(0, 0, 0));
	ground->setDynamic(false);
	ground->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	ground->setContactTestBitmask(true);
	auto groundNode = Node::create();
	groundNode->setTag(OBJECT_TAG::GROUND_TAG);
	groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.03f + origin.y));
	groundNode->setPhysicsBody(ground);
	this->addChild(groundNode);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1, 0, 0), 3);	
	edgeBody->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setTag(OBJECT_TAG::GROUND_TAG);
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	this->addChild(Background::inst()->createBackground());
	this->addChild(Background::inst()->createRock());
	this->addChild(Background::inst()->createWall());
	this->addChild(Background::inst()->createHouse());
	this->addChild(Background::inst()->createBrigde());
	Background::inst()->setSpeed(1.0f);

	Player* player = Player::create();
	player->run();
	player->setPosition(Vec2(visibleSize.width * 0.2f + origin.x, visibleSize.height * 0.5f + origin.y));
	this->addChild(player);

	Enemy* enemy = Enemy::create(ENEMY1);
	enemy->idle();
	enemy->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
	this->addChild(enemy);

	Enemy* enemy2 = Enemy::create(ENEMY2);
	enemy2->idle();
	enemy2->setPosition(Vec2(visibleSize.width * 0.7f + origin.x, visibleSize.height * 0.5f + origin.y));
	this->addChild(enemy2);

	HUDLayer* hud = HUDLayer::create();
	hud->setPlayer(player);
	this->addChild(hud);

	//event
	//  Create a "one by one" touch event listener
	// (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		// your code
		return true; // if you are consuming it
	};

	// trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event){
		// your code
	};

	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		player->jump();
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}

