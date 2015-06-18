#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "cocos2d.h"

USING_NS_CC;

class DBContext
{
private:
	static CCUserDefault* context;

public:
	static void init();

	static std::string get(const char* key);
	static void set(const char* key, std::string value);
	static boolean keyExist(const char* key);
	static void del(const char* key);
};

#endif