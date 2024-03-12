#ifndef __ARCHER5_H__
#define __ARCHER5_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;
class Archer5 : public Chess
{
public:
	static Archer5* create();
	virtual bool init();
};

#endif // !__ARCHER5_H__
