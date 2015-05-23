#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -500));
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

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1, 0, 0), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
    
    auto sprite = Sprite::create("bg_menu.png");   
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	auto rock = RockLayer::create();
	this->addChild(rock);

	auto wall = WallLayer::create();
	this->addChild(wall);



	auto house = HouseLayer::create();
	this->addChild(house);

	auto brigde = BrigdeLayer::inst();
	this->addChild(brigde);

	Player* player = Player::create();
	player->run();
	player->setPosition(Vec2(visibleSize.width * 0.2f + origin.x, visibleSize.height * 0.5f + origin.y));
	this->addChild(player);

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
		player->attack();
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}

