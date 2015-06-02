#ifndef _STORY_SCENE_H_
#define _STORY_SCENE_H_

#include "cocos2d.h"
#include "MainGameScene.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class Story : public Layer
{
private:

public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	void nextScene();
	//event
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

	CREATE_FUNC(Story);
};

#endif