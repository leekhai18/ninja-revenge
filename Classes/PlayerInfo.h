#ifndef _PLAYER_INFO_H_
#define _PLAYER_INFO_H_

#define LONGEST_RUN "player:longest_run"
#define TOTAL_PLAY_TIME "player:total_play_time"
#define TOTAL_KILL "player:total_kill"
#define KILL_BY_SLASH "player:kill_by_slash"
#define KILL_BY_SPECIAL_SKILL "player:kill_by_special_skill"

#include "DBContext.h"
class PlayerInfo
{
private:

public:
	static float longestRun, totalPlayTime;
	static int totalKill, killBySlash, killBySpecialSkill;

	static void updateFromDB();
	static void saveToDB();

	static float getLongestRun();
	static void setLongestRun(float value);

	static float getTotalPlayTime();
	static void setTotalPlayTime(float value);

	static int getTotalKill();
	static void setTotalKill(int value);

	static int getKillBySlash();
	static void setKillBySlash(int value);

	static int getKillBySpecialSkill();
	static void setKillBySpecialSkill(int value);
};

#endif