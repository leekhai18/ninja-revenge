#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#define ARROW_PATH "arrow.wav"
#define CLICK_PATH "click.wav"
#define DIE1_PATH "die1.wav"
#define DIE2_PATH "die2.wav"
#define DIE3_PATH "die3.wav"
#define DIE4_PATH "die4.wav"
#define FOOTSTEP_PATH "footsteps.wav"
#define GAME_OVER_PATH "gameover.wav"
#define HIT1_PATH "hit1.wav"
#define HIT2_PATH "hit2.wav"
#define HURT1_PATH "hurt1.wav"
#define HURT2_PATH "hurt2.wav"
#define JUMP_PATH "jump.wav"
#define LAND_PATH "land.wav"
#define POWER_UP1_PATH "powerup1.wav"
#define POWER_UP2_PATH "powerup2.wav"
#define QUEST_COMPLETE_PATH "quest_complete.wav"
#define SHIELD_OFF "shield_off.wav"
#define SHIELD_ON "shield_on.wav"
#define SKY_FALL "sky_fall.wav"
#define SLASH1_PATH "slash1.wav"
#define SLASH2_PATH "slash1.wav"
#define SPEAR_PATH "spear.wav"
#define THEME_PATH "theme.wav"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class SoundManager
{
private:
	CocosDenshion::SimpleAudioEngine* audio;
	static SoundManager* instance;
public:
	static SoundManager* inst();
	void init();

	void playBackgroundTheme(bool isLoop = true);
	void stopBackgroundTheme();

	void playArrowEffect(bool isLoop = false);
	void playClickEffect(bool isLoop = false);
	void playDie1Effect(bool isLoop = false);
	void playDie2Effect(bool isLoop = false);
	void playDie3Effect(bool isLoop = false);
	void playDie4Effect(bool isLoop = false);
	void playFootStepEffect(bool isLoop = false);
	void playGameOverEffect(bool isLoop = false);
	void playHit1Effect(bool isLoop = false);
	void playHit2Effect(bool isLoop = false);
	void playHurt1Effect(bool isLoop = false);
	void playHurt2Effect(bool isLoop = false);
	void playJumpEffect(bool isLoop = false);
	void playLandEffect(bool isLoop = false);
	void playPowerUp1Effect(bool isLoop = false);
	void playPowerUp2Effect(bool isLoop = false);
	void playQuestCompleteEffect(bool isLoop = false);
	void playShieldOffEffect(bool isLoop = false);
	void playShieldOnEffect(bool isLoop = false);
	void playSkyFallEffect(bool isLoop = false);
	void playSlash1Effect(bool isLoop = false);
	void playSlash2Effect(bool isLoop = false);
	void playSpearEffect(bool isLoop = false);

};

#endif