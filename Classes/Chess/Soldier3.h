#ifndef __SOLDIER3_H__
#define __SOLDIER3_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class Soldier3 : public Chess
{
public:
	static Soldier3* create();
	virtual bool init();
	
};

#endif // !__SOLDIER3_H__
