#include "Blood.h"


Blood* Blood::createBlood()
{
	Blood* blood = new Blood();
	if (blood && blood->init())
	{
		blood->initBlood();
		blood->autorelease();
		return blood;
	}

	CC_SAFE_DELETE(blood);
	return nullptr;
}

void Blood::initBlood()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bloodBackground = Sprite::create("Blood\\blood.png");
	bloodBackground->setScale(2);
	bloodBackground->runAction(Sequence::create(FadeOut::create(0.5f), nullptr));
	this->addChild(bloodBackground);

	int numOfBlood = random(2, 5);
	for (int i = 0; i < numOfBlood; i++)
	{
		auto blood = Sprite::create("Blood\\blood1.png");
		auto s = random(1.0f, 2.0f);
		blood->runAction(ScaleTo::create(0.3, s));
		blood->runAction(Sequence::create(FadeOut::create(1), nullptr));

		blood->setPositionX(random(-visibleSize.width * 0.5f, visibleSize.width * 0.5f));
		blood->setPositionY(random(-visibleSize.height * 0.5f, visibleSize.height * 0.5f));
		
		this->addChild(blood);
	}
	this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(Blood::autoDestroy,this)), nullptr));
}

void Blood::autoDestroy()
{
	this->getParent()->removeChild(this);
}
