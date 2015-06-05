#include "MainGameScene.h"
#include "MyBodyParser.h"

USING_NS_CC;

Scene* MainGame::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	scene->getPhysicsWorld()->setSpeed(1.5f);
	if (DEBUG_MODE)
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
	auto layer = MainGame::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto ground = PhysicsBody::createBox(Size(960*3, 10), PhysicsMaterial(0, 0, 0));
	ground->setDynamic(false);
	ground->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	ground->setContactTestBitmask(true);

	auto groundNode = Node::create();
	groundNode->setTag(OBJECT_TAG::GROUND_TAG);
	groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.03f + origin.y-20));
	groundNode->setName("Ground");
	groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.03f + origin.y));
	groundNode->setPhysicsBody(ground);
	this->addChild(groundNode);	

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

	/*auto bridge = Sprite::create("house layer\\bridge_front1.png");
	MyBodyParser::getInstance()->parseJsonFile("house layer\\bridge.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(bridge, "bridge", PhysicsMaterial(0, 0, 0));
	body->setRotationEnable(false);	
	body->setDynamic(false);
	body->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	body->setContactTestBitmask(true);
	bridge->setName("Ground");

	if (body != nullptr)
	{
		bridge->setPhysicsBody(body);
	}
	else
	{
		auto rectBody = PhysicsBody::createBox(Size(200, 30), PhysicsMaterial(0, 0, 0));		
		bridge->setPhysicsBody(rectBody);
	}
	bridge->setPosition(Vec2(visibleSize.width, 100));
	bridge->runAction(MoveBy::create(5, Vec2(-1000, 0)));
	this->addChild(bridge);*/

	HUDLayer* hud = HUDLayer::create();
	hud->setPlayer(player);
	this->addChild(hud);
    
    return true;
}

