#include "StoryScene.h"

Scene* Story::createScene()
{
	auto scene = Scene::create();
	auto layer = Story::create();
	scene->addChild(layer);

	return scene;
}

bool Story::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//quest button
	auto skipItem = MenuItemImage::create(
		BUTTON_SKIP_PATH,
		BUTTON_SKIP_PATH,
		CC_CALLBACK_1(Story::menuSkipCallback, this));
	auto menu = Menu::create(skipItem, NULL);
	menu->setPosition(visibleSize.width - skipItem->getContentSize().width, skipItem->getContentSize().height*2);
	this->addChild(menu, 1000);

	auto story = Armature::create("story");
	story->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y);
	story->getAnimation()->play("Appear");
	story->getAnimation()->setSpeedScale(0.7f);
	this->addChild(story);

	//add event listener
	story->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Story::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//even touch
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		// your code
		return true; // if you are consuming it
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		this->nextScene();
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}

void Story::nextScene()
{
	auto scene = MainGame::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene, Color3B(0, 0, 0)));
}

void Story::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Appear")
		{
			this->nextScene();
		}
	}
}

void Story::menuSkipCallback(Ref* pSender)
{
	SoundManager::inst()->playClickEffect();
	this->nextScene();
}