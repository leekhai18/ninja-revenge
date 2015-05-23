#include "Player.h"


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
	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Player::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//add physic body
	auto body = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(1, 0, 0));
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	return true;

}

void Player::update(float dt)
{
	Armature::update(dt);
}

void Player::run()
{
	this->getAnimation()->play("Run", 0, 1);
	this->setState(ESTATE::RUN);
}

void Player::jump()
{
	this->getAnimation()->play("Jump");
	this->setState(ESTATE::JUMP);
}

void Player::attack()
{
	this->getAnimation()->play("Attack");
	this->setState(ESTATE::ATTACK);
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
			this->run();
		}
	}
}

void Player::addEvent()
{
	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Player::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}