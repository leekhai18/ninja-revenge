#include "HUDLayer.h"

USING_NS_CC;

HUDLayer* HUDLayer::create()
{
	HUDLayer* hud = new HUDLayer();
	if (hud && hud->init())
	{
		hud->autorelease();

		return hud;
	}
	CC_SAFE_DELETE(hud);

	return nullptr;
}

// on "init" you need to initialize your instance
bool HUDLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	
	// add a "close" icon to exit the progress. it's an autorelease object
	auto swordItem = MenuItemImage::create(
		"UI\\b_knife.png",
		"UI\\b_knife_delay.png",
		CC_CALLBACK_1(HUDLayer::slash, this));
	
	swordItem->setPosition(visibleSize.width + origin.x - swordItem->getContentSize().width * 0.5f, 
							0 + origin.y + swordItem->getContentSize().height * 0.5f);

	// create menu, it's an autorelease object
	auto menu = Menu::create(swordItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//event
	//  Create a "one by one" touch event listener
	// (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		player->jump();
		isTouchDown = true;
		initTouchPos = Vec2(touch->getLocation().x, touch->getLocation().y);
		currentTouchPos = Vec2(touch->getLocation().x, touch->getLocation().y);
		return true; // if you are consuming it
	};

	// trigger when moving touch
	listener1->onTouchMoved = [=](Touch* touch, Event* event){
		currentTouchPos = Vec2(touch->getLocation().x, touch->getLocation().y);
	};

	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		if (player->getState() == ESTATE::JUMP || player->getState() == ESTATE::JUMP2)
			player->setHold(false);
		isTouchDown = false;
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	this->scheduleUpdate();
	return true;
}

void HUDLayer::update(float dt)
{
	if (isTouchDown == true)
	{
		if (initTouchPos.y - currentTouchPos.y > visibleSize.width * 0.05f)
		{
			CCLOG("SWIPED DOWN");
			player->flashDown();
			isTouchDown = false;
		}
		else if (initTouchPos.y - currentTouchPos.y < -visibleSize.width * 0.05f)
		{
			CCLOG("SWIPED UP");
			player->flashUp();
			isTouchDown = false;
		}
	}
}

void HUDLayer::slash(Ref* sender)
{
	player->attack();
}

