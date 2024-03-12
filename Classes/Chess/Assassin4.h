#ifndef __ASSASSIN4_H__
#define __ASSASSIN4_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Assassin4 : public Chess
{
public:
	static Assassin4* create();
	virtual bool init();
};

#endif // !__ASSASSIN4_H__
