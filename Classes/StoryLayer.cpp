#include "StoryLayer.h"

Scene* StoryLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = StoryLayer::create();
	scene->addChild(layer);

	return scene;
}

bool StoryLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto story = Armature::create("story");
	story->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y);
	story->getAnimation()->play("Appear");
	this->addChild(story);

	//add event listener
	story->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(StoryLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

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

void StoryLayer::nextScene()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene, Color3B(0, 0, 0)));
}

void StoryLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Appear")
		{
			this->nextScene();
		}
	}
}