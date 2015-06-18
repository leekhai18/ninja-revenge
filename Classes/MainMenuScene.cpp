#include "MainMenuScene.h"


Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	Sprite* bg = Sprite::create(BACKGROUND_PATH);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	this->addChild(bg);

	// add a "close" icon to exit the progress. it's an autorelease object
	auto startItem = MenuItemImage::create(
		BUTTON_START,
		BUTTON_START,
		CC_CALLBACK_1(MainMenuScene::menuPlayCallback, this));

	Vec2 startButtonPos = Vec2(visibleSize.width - startItem->getContentSize().width / 2 - startItem->getContentSize().width/4,
		origin.y + startItem->getContentSize().height / 2 + startItem->getContentSize().height / 4);
	startItem->setPosition(startButtonPos);
	
	Sprite* backgroundStartButton = Sprite::create(BACKGROUND_BUTTON_START);
	backgroundStartButton->setPosition(startButtonPos);
	//backgroundStartButton->setScale(visibleSize.width / bg->getContentSize().width);
	this->addChild(backgroundStartButton);

	CCCallFuncN* callFuncN = CCCallFuncN::create(this, callfuncN_selector(MainMenuScene::updateStartButton));
	CCDelayTime *delayAction = CCDelayTime::create(startButtonActionTime);
	startItem->runAction(CCRepeatForever::create((ActionInterval*)CCSequence::create(callFuncN, delayAction,  NULL)));

	//record button
	auto recordItem = MenuItemImage::create(
		BUTTON_RECORD,
		BUTTON_RECORD,
		CC_CALLBACK_1(MainMenuScene::menuRecordCallback, this));

	Vec2 recordButtonPos = Vec2(recordItem->getContentSize().width,
		2*recordItem->getContentSize().height/3);
	recordItem->setPosition(recordButtonPos);

	//quest button
	auto questItem = MenuItemImage::create(
		BUTTON_QUEST,
		BUTTON_QUEST,
		CC_CALLBACK_1(MainMenuScene::menuQuestCallback, this));

	Vec2 questButtonPos = Vec2(questItem->getContentSize().width + questItem->getContentSize().width + questItem->getContentSize().width/4,
		2*questItem->getContentSize().height/3);
	questItem->setPosition(questButtonPos);

	//power button
	auto PowerItem = MenuItemImage::create(
		BUTTON_POWER,
		BUTTON_POWER,
		CC_CALLBACK_1(MainMenuScene::menuPowerCallback, this));

	Vec2 powerButtonPos = Vec2(2 * PowerItem->getContentSize().width +  3*PowerItem->getContentSize().width/2,
		2*PowerItem->getContentSize().height/3);
	PowerItem->setPosition(powerButtonPos);

	//setting button
	auto settingItem = MenuItemImage::create(
		BUTTON_SETTING,
		BUTTON_SETTING,
		CC_CALLBACK_1(MainMenuScene::menuSettingCallback, this));

	Vec2 settingButtonPos = Vec2(3 * settingItem->getContentSize().width + 5 * settingItem->getContentSize().width / 3,
		2 * settingItem->getContentSize().height / 3);
	settingItem->setPosition(settingButtonPos);




	// create menu, it's an autorelease object
	cocos2d::Vector<MenuItem*> items;
	items.pushBack(startItem);
	items.pushBack(PowerItem);
	items.pushBack(questItem);
	items.pushBack(recordItem);
	items.pushBack(settingItem);
	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	this->createTable();
	//SoundManager::inst()->playBackgroundTheme(true);

	//this->showTable();
	//std::vector<std::string> lines;
	//FileWriter::writeFirstTime("deleteUser.txt");
	//FileReader::readFile("deleteUser.txt", lines);
	return true;
}

//void readFile(){
//	std::vector<std::string> lines;
//	FileReader::readFile("deleteUser.txt", lines);
//}

void MainMenuScene::updateStartButton(CCNode* sender){
	startButtonScaleFactor = startButtonScaleFactor < 1.0f ? 1.0f : 0.75f;
	ScaleTo* scaleBy = ScaleTo::create(startButtonActionTime, startButtonScaleFactor);
	RotateBy* rotate = RotateBy::create(startButtonActionTime, 69.0f);
	sender->runAction(scaleBy);
	sender->runAction(rotate);
}

void MainMenuScene::menuPlayCallback(Ref* pSender)
{
	auto storyScene = Story::createScene();
	//SoundManager::inst()->stopBackgroundTheme();
	Director::getInstance()->replaceScene(storyScene);
}

void MainMenuScene::menuSettingCallback(Ref* pSender)
{
	this->showTable();
}

void MainMenuScene::menuRecordCallback(Ref* pSender)
{
	this->showTable();
}

void MainMenuScene::menuQuestCallback(Ref* pSender)
{
	this->showTable();
}

void MainMenuScene::menuPowerCallback(Ref* pSender)
{
	this->showTable();
}

void MainMenuScene::createTable()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->tableHeader = Sprite::create(TABLE_HEADER_PATH);
	float a = visibleSize.width / tableHeader->getContentSize().width;
	tableHeader->setPosition(visibleSize.width / 2, visibleSize.height - tableHeader->getContentSize().height*a / 4);
	tableHeader->setScale(a / 2);

	//Sprite* bg = Sprite::create(BACKGROUND_PATH);
	//bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//bg->setScale(visibleSize.width / bg->getContentSize().width);


	this->bambooTop = Sprite::create(BAMBOO_TOP_PATH);
	bambooTop->setPosition(visibleSize.width / 2, tableHeader->getPosition().y - tableHeader->getContentSize().height/2);
	bambooTop->setScale(a / 2);

	this->tableContent = Sprite::create(TABLE_CONTENT_PATH);
	tableContent->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	tableContent->setScale(a/2);

	this->bambooBottom = Sprite::create(BAMBOO_BOTTOM_PATH);
	bambooBottom->setPosition(visibleSize.width / 2, tableContent->getPosition().y - tableContent->getContentSize().height*a / 4);
	bambooBottom->setScale(a / 2);

	//this->recBot = Sprite::create(TABLE_REC_EDGE_PATH);
	//recBot->setPosition(tableContent->getPosition().x - tableContent->getContentSize().width / 2, tableContent->getPosition().y - tableContent->getContentSize().height / 4);
	//recBot->setScale(a / 2);

	//this->recTop = Sprite::create(TABLE_REC_EDGE_PATH);
	//recTop->setPosition(visibleSize.width / 2, tableContent->getPosition().y - tableContent->getContentSize().height*a / 4);
	//recTop->setScale(a / 2);

	//this->recRight = Sprite::create(TABLE_REC_EDGE_PATH);
	//recRight->setPosition(visibleSize.width / 2, tableContent->getPosition().y - tableContent->getContentSize().height*a / 4);
	//recRight->setScale(a / 2);

	//this->recLeft = Sprite::create(TABLE_REC_EDGE_PATH);
	//recLeft->setPosition(tableContent->getPosition().x - tableContent->getContentSize().width/3, 
	//	tableContent->getPosition().y - tableContent->getContentSize().height*a/6);
	//recLeft->setScale(a / 3);


	//recBot->retain();
	//recTop->retain();
	//recRight->retain();
	//recLeft->retain();
	bambooBottom->retain();
	bambooTop->retain();
	tableContent->retain();
	tableHeader->retain();

}

void MainMenuScene::showTable()
{
	if (alreadyShowTable)
		return;


	this->addChild(tableContent, 699);
	this->addChild(bambooBottom, 699);
	this->addChild(bambooTop, 699);
	this->addChild(tableHeader, 699);

	//this->addChild(recBot, 699);
	//this->addChild(recLeft, 699);
	//this->addChild(recRight, 699);
	//this->addChild(recTop, 699);

	alreadyShowTable = true;
}

void MainMenuScene::hideTable()
{
	this->removeChild(bambooBottom);
	this->removeChild(bambooTop);
	this->removeChild(tableContent);
	this->removeChild(tableHeader);
}