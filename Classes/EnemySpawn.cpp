#include "EnemySpawn.h"

EnemySpawn* EnemySpawn::createEnemySpawn()
{
	EnemySpawn* spawn = new EnemySpawn();
	if (spawn && spawn->init())
	{
		spawn->initSpawn();
		spawn->autorelease();
		return spawn;
	}
	CC_SAFE_DELETE(spawn);

	return nullptr;
}

void EnemySpawn::initSpawn()
{
	timer = 0;
	level = 1;
	caculateEnemyType();
	caculateTimeToRespawn();
	timeToRespawn = random(minTime, maxTime);
	this->scheduleUpdate();
}

void EnemySpawn::caculateTimeToRespawn()
{
	minTime = 1 / (float)level + 1;
	maxTime = 3 / (float)level + 1;
	timeToRespawn = random(minTime, maxTime);
}

void EnemySpawn::caculateEnemyType()
{
	maxEnemyType = level;
}

void EnemySpawn::setLevel(int lv)
{
	level = lv;
	caculateTimeToRespawn();
	caculateEnemyType();
}

void EnemySpawn::levelUp()
{
	setLevel(level + 1);
}

void EnemySpawn::update(float dt)
{
	timer += dt;
	if (timer > timeToRespawn)
	{
		timer = 0;
		respawn();
	}
}

void EnemySpawn::respawn()
{
	int t = random(0, level);
	ENEMY_TYPE type = ENEMY_TYPE(t);
	Enemy* enemy = Enemy::create(type);
	enemy->setPlayer(player);
	enemy->setPosition(this->getPosition());

	this->getParent()->addChild(enemy);
	caculateTimeToRespawn();
}