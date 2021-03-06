#include "BrigdeLayer.h"
#include "MyBodyParser.h"

USING_NS_CC;
//BrigdeLayer* BrigdeLayer::instance = NULL;
//
//BrigdeLayer* BrigdeLayer::inst(){
//	//if (!instance){
//		instance = new BrigdeLayer();
//		instance->init();
//	//}
//	return instance;
//}

Scene* BrigdeLayer::createScene()
{
	// 'scene' is an autorelease object
	scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BrigdeLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BrigdeLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	brigde = nullptr;

	this->scheduleUpdate();

	return true;
}

void BrigdeLayer::update(float delta){

	if (brigde == nullptr)
		return;
	int x = brigde->getPosition().x;
	if (brigde->getPosition().x < -400){
		this->removeChild(brigde);
		brigde = nullptr;
	}
	else{
		brigde->setPosition(brigde->getPosition().x - delta*layerSpeed, brigde->getPosition().y);
	}

}

void BrigdeLayer::addBrigde(float xLocation){
	brigde = Sprite::create(BRIGDE_FRONT_1_PATH);
	/*MyBodyParser::getInstance()->parseJsonFile("house layer\\bridge.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(brigde, "bridge", PhysicsMaterial(0, 0, 0));
	if (body != nullptr)
	{
		this->setPhysicsBody(body);
	}
	else
	{
		auto rectBody = PhysicsBody::createBox(Size(200, 30), PhysicsMaterial(0, 0, 0));
		this->setPhysicsBody(rectBody);
	}*/
	brigde->setPosition(xLocation + brigde->getContentSize().width/2, BRIGDE_FRONT_1_HEIGHT / 2);
	this->addChild(brigde);
}