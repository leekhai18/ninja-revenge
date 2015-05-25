#ifndef __BACKGROUND_TEMPLATE_H__
#define __BACKGROUND_TEMPLATE_H__


#define BG_N_HOUSE 4
#include "cocos2d.h"
//#include "WallLayer.h"

class BackgroundTemplate : public cocos2d::Layer
{
private:
	static BackgroundTemplate* instance;
protected:
	float layerSpeed;
public:
	void setLayerSpeed(float speed);
	virtual void update(float delta) =0 ;
	virtual cocos2d::Scene* createScene() = 0;
	virtual bool init() = 0;
};

#endif 
