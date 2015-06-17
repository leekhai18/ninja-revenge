#include "Player.h"
#include "Global.h"
#include "Enemy.h"
#include "SoundManager.h"

Player::Player() : Armature(), isJumping(false), canFlash(false), flashPositionY(0),
isOnGround(false), groundPosition(0), canUseSkill1(true), timeUseSkill1(0), timeToAddNewShadow(0)
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
	contactListener->onContactPostSolve = CC_CALLBACK_2(Player::onContactPostSolve, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	return true;

}

void Player::update(float dt)
{
	Armature::update(dt);
	if (timeDelayAttack > 0)
	{
		timeDelayAttack -= dt;
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
		timeUseSkill1 += dt;
		if (timeUseSkill1 >= PLAYER_TIME_USE_SKILL1)
		{
			state = ESTATE::RUN;
			canUseSkill1 = false;
			timeUseSkill1 = 0;
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
}

void Player::run()
{
	this->getAnimation()->play("Run", 0, 1);
	this->setState(ESTATE::RUN);
	SoundManager::inst()->playFootStepEffect(true);	
}

void Player::jump()
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

void Player::setHold(bool val)
{
	isHolding = val;
}

void Player::attack()
{
	if (timeDelayAttack <= 0)
	{
		SoundManager::inst()->playSlash1Effect();
		timeDelayAttack = PLAYER_SLASH_DELAY;
		int rand = random(1, 2);
		std::string animName = "Attack";
		std::string number = std::to_string(rand);
		this->getAnimation()->play(animName + number);
		this->setState(ESTATE::ATTACK);
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

void Player::setSkill1()
{
	state = ESTATE::SKILL1;
	canUseSkill1 = true;
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
		CCLOG("HAIZ %f", a->getBoundingBox().size.height);
		if (b->getTag() == OBJECT_TAG::PLAYER_TAG)
		{
			canFlash = true;
			flashPositionY = a->boundingBox().size.height;
			
		}
		return false;
	}

	if (b->getTag() == OBJECT_TAG::HOUSE_TAG)
	{
		CCLOG("HAIZ %f", a->getBoundingBox().size.height);
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
		if (this->getState() == ESTATE::ATTACK || this->getIsUseSkill())
		{
			auto e = (Enemy*)b;
			e->setDie();
		}	
		return false;
	}

	if ((b->getTag() == OBJECT_TAG::PLAYER_TAG && a->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		if (this->getState() == ESTATE::ATTACK || this->getIsUseSkill())
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
		//if (b->getTag() == OBJECT_TAG::PLAYER_TAG == 0)
		{
			if (this->getPositionY() > groundPosition + 100 && isOnGround == true)
			{
				getPhysicsBody()->setGravityEnable(true);
				isOnGround = false;
			}
			canFlash = false;	
			CCLOG("FUCK %f", a->getBoundingBox().size.height);
		}
	}

	if (b->getTag() == OBJECT_TAG::HOUSE_TAG)
	{
		//if (a->getTag() == OBJECT_TAG::PLAYER_TAG == 0)
		{
			if (this->getPositionY() > groundPosition + 100 && isOnGround == true)
			{
				getPhysicsBody()->setGravityEnable(true);
				isOnGround = false;
			}
			canFlash = false;
			CCLOG("FUCK you %f", a->getBoundingBox().size.height);
		}
	}
}

void Player::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();

}

void Player::destroyCallback(Node* node)
{
	node->getParent()->removeChild(node);
}