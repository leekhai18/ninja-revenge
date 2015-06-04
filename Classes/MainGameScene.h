#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Global.h"
#include "HUDLayer.h"
#include "StoryScene.h"
#include "Background.h"

class MainGame : public cocos2d::Layer
{
private:
	static cocos2d::Scene* scene;
	cocos2d::PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(MainGame);
};

#endif // __HELLOWORLD_SCENE_H__
