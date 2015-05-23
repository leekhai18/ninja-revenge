#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//define some config (don't use too much)
#define DEBUG_MODE 1

class Global
{
private:
	static Global*		instance;
	static bool			instanceFlag;

	Global() 
	{

	}

public:
	//ctor & des
	~Global()
	{
		instanceFlag = false;
	}

	void init();
	Global* getInstance();

};

#endif