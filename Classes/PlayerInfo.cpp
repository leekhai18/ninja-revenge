#include "PlayerInfo.h"

int PlayerInfo::totalKill = 0;
int PlayerInfo::killBySlash = 0;
int PlayerInfo::killBySpecialSkill = 0;
float PlayerInfo::longestRun = 0.0f;
float PlayerInfo::totalPlayTime = 0.0f;;

void PlayerInfo::saveToDB(){
	DBContext::set(LONGEST_RUN, std::to_string(getLongestRun()));
	DBContext::set(TOTAL_KILL, std::to_string(getTotalKill()));
	DBContext::set(TOTAL_PLAY_TIME, std::to_string(getTotalPlayTime()));
	DBContext::set(KILL_BY_SLASH, std::to_string(getKillBySlash()));
	DBContext::set(KILL_BY_SPECIAL_SKILL, std::to_string(getKillBySpecialSkill()));
}

void PlayerInfo::updateFromDB(){
	if (!DBContext::keyExist(LONGEST_RUN)){
		saveToDB();
		return;
	}
	setLongestRun(std::stof(DBContext::get(LONGEST_RUN)));
	setTotalPlayTime(std::stof(DBContext::get(TOTAL_PLAY_TIME)));
	setTotalKill(std::stoi(DBContext::get(TOTAL_KILL)));
	setKillBySlash(std::stoi(DBContext::get(KILL_BY_SLASH)));
	setKillBySpecialSkill(std::stoi(DBContext::get(KILL_BY_SPECIAL_SKILL)));
}

float PlayerInfo::getLongestRun(){
	return longestRun;
}

void PlayerInfo::setLongestRun(float value){
	longestRun = value;
}

float PlayerInfo::getTotalPlayTime(){
	return totalPlayTime;
}

void PlayerInfo::setTotalPlayTime(float value){
	totalPlayTime = value;
}

int PlayerInfo::getTotalKill(){
	return totalKill;
}

void PlayerInfo::setTotalKill(int value){
	totalKill = value;
}

int PlayerInfo::getKillBySlash(){
	return killBySlash;
}

void PlayerInfo::setKillBySlash(int value){
	killBySlash = value;
}

int PlayerInfo::getKillBySpecialSkill(){
	return killBySpecialSkill;
}

void PlayerInfo::setKillBySpecialSkill(int value){
	killBySpecialSkill = value;
}