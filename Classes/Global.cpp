#include "Global.h"

bool Global::instanceFlag = false;
Global* Global::instance = nullptr;

bool Global::isPause = false;

void Global::init()
{
	//init something
}

Global* Global::getInstance()
{
	if (!instance)
	{
		instance = new Global();
		instance->init();
		instanceFlag = true;
	}
	return instance;
}