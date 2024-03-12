#ifndef __ARCHER4_H__
#define __ARCHER4_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;
class Archer4 : public Chess
{
public:
	static Archer4* create();
	virtual bool init();
};

#endif // !__ARCHER4_H__
