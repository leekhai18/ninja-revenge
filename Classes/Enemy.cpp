#include "Enemy.h"


Enemy* Enemy::create(ENEMY_TYPE _type)
{
	Enemy* enemy = new Enemy();

	if (enemy && enemy->initEnemy(_type))
	{
		enemy->autorelease();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);

	return nullptr;
}

bool Enemy::initEnemy(ENEMY_TYPE _type)
{
	enemyType = _type;

	if (_type == ENEMY_TYPE::ENEMY1)
	{
		this->init("enemy1");
	}
	else if (_type == ENEMY_TYPE::ENEMY2)
	{
		this->init("enemy2");
	}

	this->setTag(OBJECT_TAG::ENEMY_TAG);
	this->setName("Enemy");

	//add event listener
	this->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Enemy::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//add physic body
	auto body = PhysicsBody::createBox(Size(this->getBoundingBox().size.width * 1.8f, this->getBoundingBox().size.height), PhysicsMaterial(1, 0, 0));
	body->setRotationEnable(false);
	body->setCollisionBitmask(OBJECT_BISMASK::ENEMY_MASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);

	return true;
}

void Enemy::update(float dt)
{
	Armature::update(dt);
	this->setPositionX(this->getPositionX() - ENEMY_SPEED * dt);
	if (this->getPositionX() < 450 && this->getPositionX() > 0)
	{
		if (hasSlash == false)
		{
			hasSlash = true;
			this->attack();
		}
	}

	if (this->getPositionX() < -100)
	{
		this->setPosition(random(1500, 2000), 200);
		hasSlash = false;
		isDie = false;
		this->idle();
	}
}

void Enemy::idle()
{
	this->getAnimation()->play("Idle");
	this->setState(ESTATE::IDLE);
}

void Enemy::attack()
{
	this->getAnimation()->play("Attack");
	this->setState(ESTATE::ATTACK);	
}

void Enemy::die()
{
	this->getAnimation()->play("Die");
	this->setState(ESTATE::DIE);
}

void Enemy::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == MovementEventType::COMPLETE)
	{
		if (movementID == "Attack")
		{
			this->idle();
		}
		else if (movementID == "Die")
		{

		}
	}
}

