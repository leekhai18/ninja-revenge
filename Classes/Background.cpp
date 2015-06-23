#include "Background.h"

USING_NS_CC;

Background* Background::instance = NULL;
float Background::SPEED_UP = 1;

Background* Background::inst(){
	if (!instance){
		instance = new Background();
	}
	return instance;
}

void Background::setSpeed(float percent){
	this->backgroundLayer->setLayerSpeed(BACKGROUND_SPEED*percent);
	this->houseLayer->setLayerSpeed(GROUND_SPEED*percent);
	this->brigdeLayer->setLayerSpeed(GROUND_SPEED*percent);
	this->rockLayer->setLayerSpeed(BACKGROUND_SPEED*percent);
	this->wallLayer->setLayerSpeed(GROUND_SPEED*percent);
	SPEED_UP = percent;
}

BackgroundLayer* Background::createBackground(){
	this->backgroundLayer = new BackgroundLayer();
	backgroundLayer->init();
	backgroundLayer->setLayerSpeed(BACKGROUND_SPEED);
	return this->backgroundLayer;
}

HouseLayer* Background::createHouse(){
	this->houseLayer = new HouseLayer();
	houseLayer->init();
	houseLayer->setLayerSpeed(BACKGROUND_SPEED);
	return this->houseLayer;
}

WallLayer* Background::createWall(){
	this->wallLayer = new WallLayer();
	wallLayer->init();
	wallLayer->setLayerSpeed(BACKGROUND_SPEED);
	return this->wallLayer;
}

RockLayer* Background::createRock(){
	this->rockLayer = new RockLayer();
	rockLayer->init();
	rockLayer->setLayerSpeed(BACKGROUND_SPEED);
	return this->rockLayer;
}

BrigdeLayer* Background::createBrigde(){
	this->brigdeLayer = new BrigdeLayer();
	brigdeLayer->init();
	brigdeLayer->setLayerSpeed(BACKGROUND_SPEED);
	return this->brigdeLayer;
}

//void Background::init()
//{
//	auto bg = BackgroundLayer::create();
//	inGameScene->addChild(bg);
//
//	auto rock = RockLayer::create();
//	inGameScene->addChild(rock);
//
//	auto wall = WallLayer::create();
//	inGameScene->addChild(wall);
//
//	auto house = HouseLayer::create();
//	inGameScene->addChild(house);
//
//	auto brigde = BrigdeLayer::inst();
//	inGameScene->addChild(brigde);
//
//}