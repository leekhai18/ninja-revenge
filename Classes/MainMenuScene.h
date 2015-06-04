#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_

#define BACKGROUND_PATH "bg_menu.png"
#define BUTTON_START "button_start.png"
#define BUTTON_POWER "button_powerup.png"
#define BUTTON_RECORD "button_record.png"
#define BUTTON_SETTING "button_setting.png"
#define BUTTON_QUEST "b_quest.png"

#define BAMBOO_BOTTOM_PATH "bamboo_bottom.png"
#define BAMBOO_TOP_PATH "bamboo_top.png"
#define TABLE_CONTENT_PATH "bg_content.png"
#define TABLE_HEADER_PATH "bg_header.png"
#define TABLE_REC_EDGE_PATH "rec_edge.png"

#define BACKGROUND_BUTTON_START "background_button_start.png"

#include "cocos2d.h"
#include "StoryScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MainMenuScene : public Layer
{
private:
	Sprite* bambooBottom;
	Sprite* bambooTop;
	Sprite* tableHeader;
	Sprite* tableContent;
	Sprite* recRight;
	Sprite* recLeft;
	Sprite* recTop;
	Sprite* recBot;

	boolean alreadyShowTable = false;

	float startButtonScaleFactor = 0.75;
	float startButtonActionTime = 0.75f;
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPlayCallback(cocos2d::Ref* pSender);
	void menuPowerCallback(cocos2d::Ref* pSender);
	void menuRecordCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuQuestCallback(cocos2d::Ref* pSender);

	void updateStartButton(CCNode* sender);

	void createTable();
	void showTable();
	void hideTable();

	CREATE_FUNC(MainMenuScene);
};

#endif