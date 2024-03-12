#ifndef __ARCHER3_H__
#define __ARCHER3_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;
class Archer3 : public Chess
{
public:
	static Archer3* create();
	virtual bool init();
};

#endif // !__ARCHER3_H__
