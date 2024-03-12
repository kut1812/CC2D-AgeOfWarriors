#ifndef __ASSASSIN5_H__
#define __ASSASSIN5_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Assassin5 : public Chess
{
public:
	static Assassin5* create();
	virtual bool init();
};

#endif // !__ASSASSIN5_H__
