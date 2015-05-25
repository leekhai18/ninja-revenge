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

	auto visibleSize = Director::getInstance()->getVisibleSize();
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

	return true;
}

void HUDLayer::slash(Ref* sender)
{
	player->attack();
}

