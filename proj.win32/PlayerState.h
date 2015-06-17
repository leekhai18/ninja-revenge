#ifndef _PLAYER_STATE_
#define _PLAYER_STATE_

#include "Player.h"

class PlayerState
{
public:	
	virtual ~PlayerState(){}
	virtual void handleInput(Player *player){}
	virtual void update(Player *player, float dt){} 
};

class Skill1 : public PlayerState
{
private:

public:

};
#endif