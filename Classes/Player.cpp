#include "Player.h"
#include "Global.h"

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

	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Player::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//add physic body
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
}

void Player::run()
{
	this->getAnimation()->play("Run", 0, 1);
	this->setState(ESTATE::RUN);
}

void Player::jump()
{
	if (!isJumping && state == ESTATE::RUN) {
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
			auto vel = getPhysicsBody()->getVelocity();
			vel.y = PLAYER_JUMP_SPEED;
			getPhysicsBody()->setVelocity(vel);
			this->getAnimation()->play("Jump2");
			this->setState(ESTATE::JUMP2);			
		}
	}
}

void Player::attack()
{
	if (timeDelayAttack <= 0)
	{
		timeDelayAttack = PLAYER_SLASH_DELAY;
		this->getAnimation()->play("Attack");
		this->setState(ESTATE::ATTACK);
	}
}

void Player::die()
{
	this->getAnimation()->play("Die");
	this->setState(ESTATE::DIE);
}

void Player::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Attack")
		{
			this->run();
		}
		else if (movementID == "Jump")
		{
			
		}
	}
}

bool Player::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();
	
	CCLOG("onContactBegin: %d vs %d", a->getTag(), b->getTag());
	if (a->getTag() == OBJECT_TAG::GROUND_TAG || b->getTag() == OBJECT_TAG::GROUND_TAG)
	{
		isJumping = false;
		this->run();
	}
	//bodies can collide
	return true;
}