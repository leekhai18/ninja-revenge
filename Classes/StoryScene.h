#ifndef _STORY_SCENE_H_
#define _STORY_SCENE_H_

#define  BUTTON_SKIP_PATH "b_skip.png"

#include "cocos2d.h"
#include "SoundManager.h"
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


	void menuSkipCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Story);
};

#endif