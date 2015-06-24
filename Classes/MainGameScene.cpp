#include "MainGameScene.h"
#include "MyBodyParser.h"
#include "EnemySpawn.h"


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

	auto ground = PhysicsBody::createBox(Size(960*3, 100), PhysicsMaterial(0, 0, 0));
	ground->setDynamic(false);
	ground->setCollisionBitmask(OBJECT_BISMASK::GROUND_MASK);
	ground->setContactTestBitmask(true);

	auto groundNode = Node::create();
	groundNode->setTag(OBJECT_TAG::GROUND_TAG);	
	groundNode->setName("Ground");
	groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * (-0.03) + origin.y));
	groundNode->setPhysicsBody(ground);
	this->addChild(groundNode);	

	this->addChild(Background::inst()->createBackground());
	this->addChild(Background::inst()->createRock());
	this->addChild(Background::inst()->createWall());
	this->addChild(Background::inst()->createHouse());
	this->addChild(Background::inst()->createBrigde());
	Background::inst()->setSpeed(2.0f);

	Player* player = Player::create();
	player->run();
	player->setPosition(Vec2( 0, visibleSize.height * 0.7 + origin.y));
	player->runAction(MoveBy::create(2, Vec2(visibleSize.width * 0.2f, 0)));
	this->addChild(player, kPlayer);

	EnemySpawn* enemySpaw = EnemySpawn::createEnemySpawn();
	enemySpaw->setPlayer(player);
	enemySpaw->setPosition(visibleSize.width * 1.5, visibleSize.height * 0.8);
	this->addChild(enemySpaw);

	HUDLayer* hud = HUDLayer::create();
	hud->setPlayer(player);
	this->addChild(hud, kHUD);

    return true;
}

