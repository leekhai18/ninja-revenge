#include "Dialog.h"
#include "ui\CocosGUI.h"
#include "Global.h"
#include "MainGameScene.h"
#include "MainMenuScene.h"
#include "StoryScene.h"
#include "Background.h"

using namespace ui;

Dialog* Dialog::createDialog(Node* header, Node* contain)
{
	Dialog* dialog = new Dialog();
	if (dialog && dialog->init("Dialog"))
	{
		dialog->initDialog(header, contain);
		dialog->autorelease();
		return dialog;
	}
	CC_SAFE_DELETE(dialog);
	return nullptr;
}

void Dialog::initDialog(Node* header, Node* contain)
{
	this->getAnimation()->play("Appear", 0);

	Bone* bone_header = Bone::create("header");
	bone_header->addDisplay(header, 0);
	bone_header->changeDisplayWithIndex(0, true);
	//b1->setIgnoreMovementBoneData(true);
	bone_header->setLocalZOrder(100);
	this->addBone(bone_header, "Header");
	
	contain->setVisible(false);
	contain->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(Dialog::visibleCallback, this, contain)), nullptr));
	this->addChild(contain, 1);
	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Dialog::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	this->scheduleUpdate();
}

void Dialog::update(float dt)
{
	Armature::update(dt);
}

void Dialog::visibleCallback(Node* node)
{
	node->setVisible(true);
}

void Dialog::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Appear")
		{

		}
		else if (movementID == "Disappear")
		{

		}
	}
}

PauseDialog* PauseDialog::createPauseDialog()
{
	PauseDialog* pause = new PauseDialog();
	if (pause && pause->init("Dialog"))
	{
		pause->initPauseDialog();
		pause->autorelease();
		return pause;
	}
	CC_SAFE_DELETE(pause);
	return nullptr;
}

void PauseDialog::initPauseDialog()
{
	auto header = Sprite::create("UI\\h_paused.png");

	auto contain = Node::create();
	auto size = Sprite::create("UI\\bg_content.png")->getContentSize();
	
	auto resume = Button::create("UI\\b_resume.png");
	resume->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			this->getAnimation()->play("Disappear", 0);
			this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(PauseDialog::onResume, this, this)), nullptr));
			break;
		}
	});
	resume->setPositionY(size.height * 0.15);
	contain->addChild(resume);

	auto retry = Button::create("UI\\b_retry.png");
	retry->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:			
			this->getAnimation()->play("Disappear", 0);
			this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(PauseDialog::onRetry, this, this)), nullptr));
			break;
		}
	});
	
	contain->addChild(retry);

	auto home = Button::create("UI\\b_home.png");
	home->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:			
			this->getAnimation()->play("Disappear", 0);
			this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(PauseDialog::onHome, this, this)), nullptr));
			break;
		}
	});
	home->setPositionY(-size.height*0.15);
	contain->addChild(home);

	this->initDialog(header, contain);
}

void PauseDialog::onResume(Node* node)
{
	node->getParent()->removeChild(node);
	Global::isPause = false;
	Background::inst()->setSpeed(1);
}

void PauseDialog::onRetry(Node* node)
{
	node->getParent()->removeChild(node);
	Global::isPause = false;
	Director::getInstance()->replaceScene(Story::createScene());
	Background::inst()->setSpeed(1);
}

void PauseDialog::onHome(Node* node)
{
	node->getParent()->removeChild(node);
	Global::isPause = false;
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
	Background::inst()->setSpeed(1);
}

DieDialog* DieDialog::createDieDialog()
{
	DieDialog* die = new DieDialog();
	if (die && die->init("Dialog"))
	{
		die->initDieDialog();
		die->autorelease();
		return die;
	}
	CC_SAFE_DELETE(die);
	return nullptr;
}

void DieDialog::initDieDialog()
{
	auto header = Sprite::create("UI\\h_die.png");

	auto contain = Node::create();
	auto size = Sprite::create("UI\\bg_content.png")->getContentSize();

	auto retry = Button::create("UI\\b_tryagain.png");
	retry->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:			
			this->getAnimation()->play("Disappear", 0);
			this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(DieDialog::onRetry, this, this)), nullptr));
			break;
		}
	});

	contain->addChild(retry);

	auto home = Button::create("UI\\b_home.png");
	home->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:			
			this->getAnimation()->play("Disappear", 0);
			this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(DieDialog::onHome, this, this)), nullptr));
			break;
		}
	});
	home->setPositionY(-size.height*0.15);
	contain->addChild(home);

	this->initDialog(header, contain);
}

void DieDialog::onRetry(Node* node)
{
	node->getParent()->removeChild(node);
	Global::isPause = false;
	Director::getInstance()->replaceScene(Story::createScene());
	Background::inst()->setSpeed(1);
}

void DieDialog::onHome(Node* node)
{
	node->getParent()->removeChild(node);
	Global::isPause = false;
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
	Background::inst()->setSpeed(1);
}