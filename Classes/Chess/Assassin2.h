#ifndef __ASSASSIN2_H__
#define __ASSASSIN2_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Assassin2 : public Chess
{
public:
	static Assassin2* create();
	virtual bool init();
};

#endif // !__ASSASSIN2_H__
