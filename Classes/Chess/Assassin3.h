#ifndef __ASSASSIN3_H__
#define __ASSASSIN3_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Assassin3 : public Chess
{
public:
	static Assassin3* create();
	virtual bool init();
};

#endif // !__ASSASSIN3_H__
