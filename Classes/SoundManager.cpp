#include "SoundManager.h"
USING_NS_CC;
SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::inst(){
	if (!instance){
		instance = new SoundManager();
		instance->init();
	}
	return instance;
}

void SoundManager::init(){
	this->audio = CocosDenshion::SimpleAudioEngine::getInstance();

	this->audio->preloadBackgroundMusic("theme.wav");

	this->audio->preloadEffect(ARROW_PATH);
	this->audio->preloadEffect(CLICK_PATH);
	this->audio->preloadEffect(DIE1_PATH);
	this->audio->preloadEffect(DIE2_PATH);
	this->audio->preloadEffect(DIE3_PATH);
	this->audio->preloadEffect(DIE4_PATH);
	this->audio->preloadEffect(FOOTSTEP_PATH);
	this->audio->preloadEffect(GAME_OVER_PATH);
	this->audio->preloadEffect(HIT1_PATH);
	this->audio->preloadEffect(HIT2_PATH);
	this->audio->preloadEffect(HURT1_PATH);
	this->audio->preloadEffect(HURT1_PATH);
	this->audio->preloadEffect(JUMP_PATH);
	this->audio->preloadEffect(LAND_PATH);
	this->audio->preloadEffect(POWER_UP1_PATH);
	this->audio->preloadEffect(POWER_UP2_PATH);
	this->audio->preloadEffect(QUEST_COMPLETE_PATH);
	this->audio->preloadEffect(SHIELD_ON);
	this->audio->preloadEffect(SHIELD_OFF);
	this->audio->preloadEffect(SKY_FALL);
	this->audio->preloadEffect(SLASH1_PATH);
	this->audio->preloadEffect(SLASH2_PATH);
	this->audio->preloadEffect(SPEAR_PATH);
}


void SoundManager::playBackgroundTheme(bool isLoop){
	this->audio->playBackgroundMusic("theme.wav", true);
}

void SoundManager::stopBackgroundTheme(){
	this->audio->stopBackgroundMusic();
}

void SoundManager::playArrowEffect(bool isLoop){
	this->audio->playEffect(ARROW_PATH, isLoop);
}

void SoundManager::playClickEffect(bool isLoop){
	this->audio->playEffect(CLICK_PATH, isLoop);
}

void SoundManager::playDie1Effect(bool isLoop){
	this->audio->playEffect(DIE1_PATH, isLoop);
}

void SoundManager::playDie2Effect(bool isLoop){
	this->audio->playEffect(DIE2_PATH, isLoop);
}

void SoundManager::playDie3Effect(bool isLoop){
	this->audio->playEffect(DIE2_PATH, isLoop);
}

void SoundManager::playDie4Effect(bool isLoop){
	this->audio->playEffect(DIE4_PATH, isLoop);
}

void SoundManager::playFootStepEffect(bool isLoop){
	this->audio->playEffect(FOOTSTEP_PATH, isLoop);
}

void SoundManager::playGameOverEffect(bool isLoop){
	this->audio->playEffect(GAME_OVER_PATH, isLoop);
}

void SoundManager::playHit1Effect(bool isLoop){
	this->audio->playEffect(HIT1_PATH, isLoop);
}

void SoundManager::playHit2Effect(bool isLoop){
	this->audio->playEffect(HIT2_PATH, isLoop);
}

void SoundManager::playHurt1Effect(bool isLoop){
	this->audio->playEffect(HURT1_PATH, isLoop);
}

void SoundManager::playHurt2Effect(bool isLoop){
	this->audio->playEffect(HURT2_PATH, isLoop);
}

void SoundManager::playJumpEffect(bool isLoop){
	this->audio->playEffect(JUMP_PATH, isLoop);
}

void SoundManager::playLandEffect(bool isLoop){
	this->audio->playEffect(LAND_PATH, isLoop);
}

void SoundManager::playPowerUp1Effect(bool isLoop){
	this->audio->playEffect(POWER_UP1_PATH, isLoop);
}

void SoundManager::playPowerUp2Effect(bool isLoop){
	this->audio->playEffect(POWER_UP2_PATH, isLoop);
}

void SoundManager::playQuestCompleteEffect(bool isLoop){
	this->audio->playEffect(QUEST_COMPLETE_PATH, isLoop);
}

void SoundManager::playShieldOffEffect(bool isLoop){
	this->audio->playEffect(SHIELD_OFF, isLoop);
}

void SoundManager::playShieldOnEffect(bool isLoop){
	this->audio->playEffect(SHIELD_ON, isLoop);
}

void SoundManager::playSkyFallEffect(bool isLoop){
	this->audio->playEffect(ARROW_PATH, isLoop);
}

void SoundManager::playSlash1Effect(bool isLoop){
	this->audio->playEffect(SKY_FALL, isLoop);
}

void SoundManager::playSlash2Effect(bool isLoop){
	this->audio->playEffect(SLASH2_PATH, isLoop);
}


void SoundManager::playSpearEffect(bool isLoop){
	this->audio->playEffect(SPEAR_PATH, isLoop);
}