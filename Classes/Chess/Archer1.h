#ifndef __ARCHER1_H__
#define __ARCHER1_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;
class Archer1 : public Chess
{
public:
	static Archer1* create();
	virtual bool init();
};

#endif // !__ARCHER1_H__
