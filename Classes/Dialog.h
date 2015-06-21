#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class Dialog : public Armature
{
public:
	static Dialog* createDialog(Node* header, Node* contain);

	virtual void update(float dt);

	void initDialog(Node* header, Node* contain);
	void onQuit();

	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	
	void visibleCallback(Node* node);
};

class PauseDialog : public Dialog
{
private:
	
public:
	static PauseDialog* createPauseDialog();

	void initPauseDialog();
	void onResume(Node* node);
	void onRetry(Node* node);
	void onHome(Node* node);
};

class DieDialog : public Dialog
{
private:

public:
	static DieDialog* createDieDialog();

	void initDieDialog();
	void onResume(Node* node);
	void onRetry(Node* node);
	void onHome(Node* node);
};
#endif