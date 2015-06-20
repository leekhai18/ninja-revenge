#include "Player.h"
#include "Global.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "Background.h"

Player::Player() : Armature()
{
	
}

Player::~Player()
{
	
}

Player* Player::create()
{
	Player* player = new Player();

	if (player && player->init("player"))
	{
		player->initPlayer();
		player->autorelease();

		return player;
	}

	CC_SAFE_DELETE(player);

	return nullptr;
}

bool Player::initPlayer()
{
	visisbleSize = Director::getInstance()->getVisibleSize();
	this->setTag(OBJECT_TAG::PLAYER_TAG);
	this->setName("Player");

	this->getAnimation()->play("Jump2");
	this->setState(ESTATE::JUMP2);

	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Player::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//add physic
	auto body = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(1, 0, 0));
	body->setRotationEnable(false);
	body->setCollisionBitmask(OBJECT_BISMASK::PLAYER_MASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);

	//add collision detetion
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(Player::onContactSeperate, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	return true;

}

void Player::update(float dt)
{
	Armature::update(dt);
	if (timeDelayAttack <= PLAYER_SLASH_DELAY)
	{
		timeDelayAttack += dt;
	}

	if (isHolding && (state == ESTATE::JUMP || state == ESTATE::JUMP2 ))
	{
		if (timeHolding > 0)
		{
			timeHolding -= dt;
			auto vel = getPhysicsBody()->getVelocity();
			vel.y = PLAYER_JUMP_SPEED;
			getPhysicsBody()->setVelocity(vel);
		}
		else
		{
			isHolding = false;
		}
	}

	if (canUseSkill1)
	{
		
	}
	else
	{
		timeCoolDownSkill1 += dt;
		if (timeCoolDownSkill1 >= PLAYER_SKILL1_COOLDOWN)
		{
			canUseSkill1 = true;
			timeCoolDownSkill1 = 0;
		}
	}

	if (isUsingSkill1)
	{
		timeOfSkill1 += dt;
		if (timeOfSkill1 >= PLAYER_TIME_USE_SKILL1)
		{
			state = ESTATE::RUN;
			canUseSkill1 = false;
			isUsingSkill1 = false;
			timeOfSkill1 = 0;
			timeCoolDownSkill1 = 0;
			Background::inst()->setSpeed(1);
		}
		else
		{
			timeToAddNewShadow += dt;
			if (timeToAddNewShadow > 0.2f)
			{
				timeToAddNewShadow = 0;
				this->addAShadow();
			}
		}
	}

	if (canUseSkill2)
	{

	}
	else
	{
		timeCoolDownSkill2 += dt;
		if (timeCoolDownSkill2 >= PLAYER_SKILL2_COOLDOWN)
		{
			canUseSkill2 = true;
			timeCoolDownSkill2 = 0;
		}
	}

	if (isUsingSkill2)
	{
		timeOfSkill2 += dt;
		if (timeOfSkill2 >= PLAYER_TIME_USE_SKILL2)
		{
			state = ESTATE::RUN;
			canUseSkill2 = false;
			isUsingSkill2 = false;
			timeOfSkill2 = 0;
			timeCoolDownSkill2 = 0;
			Background::inst()->setSpeed(1);
			this->stopAllActions();
			this->run();
			this->setPositionY(groundPosition);
		}
		else
		{
			
		}
	}
}

void Player::run()
{
	if (!isUsingSkill2)
	{
		this->getAnimation()->play("Run", 0, 1);
		this->setState(ESTATE::RUN);
		SoundManager::inst()->playFootStepEffect(true);
	}
}

void Player::jump()
{
	if (!isUsingSkill2)
	{
		if (!isJumping && (state == ESTATE::RUN || state == ESTATE::ATTACK)) {
			SoundManager::inst()->playJumpEffect();
			dirtPlay();
			timeHolding = PLAYER_TIME_HOLDING;
			isHolding = true;
			auto vel = getPhysicsBody()->getVelocity();
			vel.y = PLAYER_JUMP_SPEED;
			getPhysicsBody()->setVelocity(vel);
			getPhysicsBody()->setGravityEnable(true);
			isOnGround = false;
			this->getAnimation()->play("Jump");
			this->setState(ESTATE::JUMP);
			isJumping = true;
		}
		else
		{
			if (isJumping && state == ESTATE::JUMP) {
				SoundManager::inst()->playJumpEffect();
				timeHolding = PLAYER_TIME_HOLDING;
				isHolding = true;
				auto vel = getPhysicsBody()->getVelocity();
				vel.y = PLAYER_JUMP_SPEED;
				getPhysicsBody()->setVelocity(vel);
				this->getAnimation()->play("Jump2");
				this->setState(ESTATE::JUMP2);
			}
		}
	}	
}

void Player::setHold(bool val)
{
	isHolding = val;
}

void Player::attack()
{
	if (timeDelayAttack >= PLAYER_SLASH_DELAY && !isUsingSkill2)
	{
		SoundManager::inst()->playSlash1Effect();
		timeDelayAttack = 0;
		int rand = random(1, 2);
		std::string animName = "Attack";
		std::string number = std::to_string(rand);
		this->getAnimation()->play(animName + number);
		this->setState(ESTATE::ATTACK);
	}
}

void Player::useOmislash()
{
	if (canUseSkill1)
	{
		Background::inst()->setSpeed(1.5f);	
		isUsingSkill1 = true;
		canUseSkill1 = false;
	}
}

void Player::useBladeStorm()
{
	if (canUseSkill2)
	{
		Background::inst()->setSpeed(1.7f);
		state = ESTATE::SKILL2;
		isUsingSkill2 = true;
		canUseSkill2 = false;
		this->getAnimation()->play("Skill2");
		this->runAction(RepeatForever::create(Sequence::create(MoveTo::create(0.5f, Vec2(this->getPositionX(), visisbleSize.height * 0.9f)),
			MoveTo::create(0.5f, Vec2(this->getPositionX(), visisbleSize.height * 0.1f)),
			nullptr)));
	}
}

void Player::setDie()
{
	this->getAnimation()->play("Die");
	this->setState(ESTATE::DIE);
}

void Player::flashUp()
{
	if (canFlash)
	{
		this->getAnimation()->play("FlashUp");
	}
}

void Player::flashDown()
{
	if (canFlash)
	{
		this->getAnimation()->play("FlashDown");
	}
}

void Player::setHit(int damage)
{
	CCLOG("Hit %d damage", damage);
	SoundManager::inst()->playHurt1Effect();
	hitPoint -= damage;
	if (hitPoint <= 0)
	{
		this->setDie();
	}
}

void Player::addAShadow()
{
	Armature* shadow = Armature::create("player");
	shadow->setPosition(this->getPosition() - Vec2(0, 30));
	int currentIndex = this->getAnimation()->getCurrentFrameIndex();
	if (currentIndex < 0)
		currentIndex = 0;
	shadow->getAnimation()->play(this->getAnimation()->getCurrentMovementID(), currentIndex);
	shadow->getAnimation()->gotoAndPlay(currentIndex);
	shadow->getAnimation()->setSpeedScale(0);
	shadow->runAction(Sequence::create(MoveBy::create(1, Vec2(-700, 0)), CallFunc::create(CC_CALLBACK_0(Player::destroyCallback, this, shadow)), nullptr));
	shadow->setColor(Color3B(Color4F(180, 180, 180, 0.1f)));
	this->getParent()->addChild(shadow, 0);
}

void Player::useSkill1()
{
	if (canUseSkill1 && !isUsingSkill2)
	{
		state = ESTATE::SKILL1;
		isUsingSkill1 = true;
		canUseSkill1 = false;
	}
}

void Player::dirtPlay()
{	
	Armature* dirt = Armature::create("dirt");
	dirt->runAction(Sequence::create(DelayTime::create(1) , CallFunc::create(CC_CALLBACK_0(Player::destroyCallback, this, dirt)), nullptr));
	dirt->getAnimation()->play("idle", 0, 0);
	dirt->setPosition(this->getPosition() - Vec2(this->boundingBox().size.width * 0.35f, this->boundingBox().size.height * 0.45f));	
	this->getParent()->addChild(dirt);
}

void Player::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Attack1" || movementID == "Attack2")
		{
			this->run();
		}
		else if (movementID == "FlashUp")
		{
			this->run();
			this->setPosition(this->getPosition().x, flashPositionY);
		}
		else if (movementID == "FlashDown")
		{
			this->run();
			this->setPosition(Director::getInstance()->getVisibleSize()*0.1f);
		}
	}
}

bool Player::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();
	
	// Check collision player with ground
	if (a->getTag() == OBJECT_TAG::GROUND_TAG && b->getTag() == OBJECT_TAG::PLAYER_TAG)
	{		
		if (a->getPosition().y + a->getParent()->getPosition().y < b->getPosition().y && isOnGround == false)
		{
			isJumping = false;
			isOnGround = true;

			if (groundPosition == 0)
				groundPosition = this->getPositionY();
			this->getPhysicsBody()->setVelocity(Vec2(0, 0));
			this->getPhysicsBody()->setGravityEnable(false);

			if (state != ESTATE::ATTACK)
			{
				this->run();
			}
			dirtPlay();
			
			return true;
		}
		else
		{
			return false;
		}		
	}
	
	if (b->getTag() == OBJECT_TAG::GROUND_TAG && a->getTag() == OBJECT_TAG::PLAYER_TAG && isOnGround == false)
	{
		if (b->getPosition().y + b->getParent()->getPosition().y < a->getPosition().y)
		{
			isJumping = false;
			isOnGround = true;

			if (groundPosition == 0)
				groundPosition = this->getPositionY();
			this->getPhysicsBody()->setVelocity(Vec2(0, 0));
			this->getPhysicsBody()->setGravityEnable(false);

			if (state != ESTATE::ATTACK)
			{
				this->run();
			}
			dirtPlay();

			return true;
		}
		else
		{
			return false;
		}
	}

	// Check collision player with house
	if (a->getTag() == OBJECT_TAG::HOUSE_TAG)
	{			
		if (b->getTag() == OBJECT_TAG::PLAYER_TAG)
		{
			canFlash = true;
			flashPositionY = a->boundingBox().size.height;
			
		}
		return false;
	}

	if (b->getTag() == OBJECT_TAG::HOUSE_TAG)
	{		
		if (a->getTag() == OBJECT_TAG::PLAYER_TAG)
		{
			canFlash = true;
			flashPositionY = b->boundingBox().size.height;
			
		}
		return false;
	}

	// Check collision with enemy
	if ((a->getTag() == OBJECT_TAG::PLAYER_TAG && b->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		if (this->getState() == ESTATE::ATTACK || this->getIsUseSkill1())
		{
			auto e = (Enemy*)b;
			e->setDie();
		}	
		return false;
	}

	if ((b->getTag() == OBJECT_TAG::PLAYER_TAG && a->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		if (this->getState() == ESTATE::ATTACK || this->getIsUseSkill1())
		{
			auto e = (Enemy*)a;
			e->setDie();
		}
		return false;
	}

	if ((a->getTag() == OBJECT_TAG::ENEMY_TAG && b->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		return false;
	}

	//bodies can collide
	return true;
}

void Player::onContactSeperate(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();

	if (a->getTag() == OBJECT_TAG::PLAYER_TAG)
	{
		//CCLOG("Name: %d ", b->getTag());
	}
	else
	{
		//CCLOG("Name: %d ", a->getTag());
	}

	// Check collision player with house
	if (a->getTag() == OBJECT_TAG::HOUSE_TAG)
	{
		if (isUsingSkill2)
			return;
		//if (b->getTag() == OBJECT_TAG::PLAYER_TAG == 0)
		{
			if (this->getPositionY() > groundPosition + 100 && isOnGround == true)
			{
				getPhysicsBody()->setGravityEnable(true);
				isOnGround = false;
			}
			canFlash = false;		
		}
	}

	if (b->getTag() == OBJECT_TAG::HOUSE_TAG)
	{
		if (isUsingSkill2)
			return;
		//if (a->getTag() == OBJECT_TAG::PLAYER_TAG == 0)
		{
			if (this->getPositionY() > groundPosition + 100 && isOnGround == true)
			{
				getPhysicsBody()->setGravityEnable(true);
				isOnGround = false;
			}
			canFlash = false;			
		}
	}
}


void Player::destroyCallback(Node* node)
{
	node->getParent()->removeChild(node);
}

bool Player::canAttack()
{
	return this->timeDelayAttack > PLAYER_SLASH_DELAY;
}

bool Player::canBladeStorm()
{
	return canUseSkill2;
}

bool Player::canOmiSlash()
{
	return canUseSkill1;
}

int Player::getHP()
{
	return this->hitPoint;
}

int Player::getMaxHP()
{
	return PLAYER_MAX_HP;
}