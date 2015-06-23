#include "BackgroundTemplate.h"

USING_NS_CC;
BackgroundTemplate* BackgroundTemplate::instance = NULL;

void BackgroundTemplate::setLayerSpeed(float speed){
	this->layerSpeed = speed;
}

float BackgroundTemplate::getLayerSpeed(){
	return this->layerSpeed;
}

