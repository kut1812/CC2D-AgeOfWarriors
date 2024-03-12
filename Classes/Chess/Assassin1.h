#ifndef __ASSASSIN1_H__
#define __ASSASSIN1_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Assassin1 : public Chess
{
public:
	static Assassin1* create();
	virtual bool init();
};

#endif // !__ASSASSIN1_H__
