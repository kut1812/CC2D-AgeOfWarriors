#ifndef __ARCHER2_H__
#define __ARCHER2_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;
class Archer2 : public Chess
{
public:
	static Archer2* create();
	virtual bool init();
};

#endif // !__ARCHER2_H__
