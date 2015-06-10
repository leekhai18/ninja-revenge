#include "Enemy.h"
#include "Player.h"

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
	visibleSize = Director::getInstance()->getVisibleSize();
	enemyType = _type;

	if (_type == ENEMY_TYPE::ENEMY1)
	{
		this->init("enemy1");
		dictanceToSplash = visibleSize.width * 0.4;
	}
	else if (_type == ENEMY_TYPE::ENEMY2)
	{
		this->init("enemy2");
		dictanceToSplash = visibleSize.width * 0.4;
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

	//add collision detetion
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Enemy::onContactBegin, this);	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void Enemy::update(float dt)
{
	Armature::update(dt);
	this->setPositionX(this->getPositionX() - ENEMY_SPEED * dt);
	if (this->getPositionX() < dictanceToSplash)
	{
		if (isAttacked == false)
		{
			isAttacked = true;
			this->attack();
		}
	}

	if (this->getPositionX() < -200)
	{
		this->getParent()->removeChild(this);
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

bool Enemy::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();

	// Check collision player with ground
	if (a->getTag() == OBJECT_TAG::GROUND_TAG && b->getTag() == OBJECT_TAG::ENEMY_TAG)
	{
		if (isOnGround == false)
		{
			isOnGround == true;
			getPhysicsBody()->setGravityEnable(false);
			getPhysicsBody()->setVelocity(Vec2(0, 0));
			return true;
		}
		return false;
	}

	if (b->getTag() == OBJECT_TAG::GROUND_TAG && a->getTag() == OBJECT_TAG::ENEMY_TAG)
	{
		if (isOnGround == false)
		{
			isOnGround == true;
			getPhysicsBody()->setGravityEnable(false);
			getPhysicsBody()->setVelocity(Vec2(0, 0));
			return true;
		}
		return false;
	}

	// Check collision with enemy
	if ((a->getTag() == OBJECT_TAG::PLAYER_TAG && b->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		auto p = (Player*)a;
		if (p->getState() == ESTATE::ATTACK)
		{
			auto e = (Enemy*)b;
			e->die();
		}
		return false;
	}

	if ((b->getTag() == OBJECT_TAG::PLAYER_TAG && a->getTag() == OBJECT_TAG::ENEMY_TAG))
	{
		auto p = (Player*)b;
		if (p->getState() == ESTATE::ATTACK)
		{
			auto e = (Enemy*)a;
			e->die();
		}
		return false;
	}

	return false;
}