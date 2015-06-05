#include "Player.h"
#include "Global.h"
#include "Enemy.h"

Player::Player() : Armature(), isJumping(false)
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
}

void Player::run()
{
	this->getAnimation()->play("Run", 0, 1);
	this->setState(ESTATE::RUN);
}

void Player::jump()
{
	if (!isJumping && (state == ESTATE::RUN || state == ESTATE::ATTACK)) {
		dirtPlay();
		timeHolding = PLAYER_TIME_HOLDING;
		isHolding = true;
		auto vel = getPhysicsBody()->getVelocity();
		vel.y = PLAYER_JUMP_SPEED;	
		getPhysicsBody()->setVelocity(vel);
		this->getAnimation()->play("Jump");		
		this->setState(ESTATE::JUMP);
		isJumping = true;
	}
	else
	{
		if (isJumping && state == ESTATE::JUMP) {
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
		timeDelayAttack = PLAYER_SLASH_DELAY;
		int rand = random(1, 2);
		std::string animName = "Attack";
		std::string number = std::to_string(rand);
		this->getAnimation()->play(animName + number);
		this->setState(ESTATE::ATTACK);
	}
}

void Player::die()
{
	this->getAnimation()->play("Die");
	this->setState(ESTATE::DIE);
}

void Player::flashUp()
{
	this->getAnimation()->play("FlashUp");
}

void Player::flashDown()
{
	this->getAnimation()->play("FlashDown");
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
		}
		else if (movementID == "FlashDown")
		{
			this->run();
		}
	}
}

bool Player::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();
	
	// Check collision player with ground
	if ((a->getName().compare("Ground") == 0 && b->getName().compare("Player") == 0))
	{		
		if (a->getPosition().y + a->getParent()->getPosition().y < b->getPosition().y)
		{
			isJumping = false;
			dirtPlay();
			this->run();
			return true;
		}
		else
		{
			return false;
		}		
	}

	if ((b->getName().compare("Ground") == 0 && a->getName().compare("Player") == 0))
	{
		CCLOG("Ground Y: %f", b->getPosition().y + b->getParent()->getPosition().y);
		CCLOG("Player Y: %f", a->getPosition().y);
		if (b->getPosition().y + b->getParent()->getPosition().y< a->getPosition().y)
		{
			isJumping = false;
			dirtPlay();
			this->run();
			return true;
		}
		else
		{
			return false;
		}
	}

	// Check collision with enemy
	if ((a->getTag() == OBJECT_TAG::PLAYER_TAG && b->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		if (this->getState() == ESTATE::ATTACK)
		{
			auto e = (Enemy*)b;
			e->die();
		}	
		return false;
	}

	if ((b->getTag() == OBJECT_TAG::PLAYER_TAG && a->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		if (this->getState() == ESTATE::ATTACK)
		{
			auto e = (Enemy*)a;
			e->die();
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

void Player::destroyCallback(Node* node)
{
	node->getParent()->removeChild(node);
}