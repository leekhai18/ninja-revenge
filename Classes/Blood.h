#ifndef _BLOOD_H_
#define _BLOOD_H_

#include "cocos2d.h"

USING_NS_CC;

class Blood : public Node
{
public:
	static Blood* createBlood();

	void initBlood();
	
	void autoDestroy();
};

#endif
