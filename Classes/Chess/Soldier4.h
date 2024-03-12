#ifndef __SOLDIER4_H__
#define __SOLDIER4_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class Soldier4 : public Chess
{
public:
	static Soldier4* create();
	virtual bool init();
	
};

#endif // !__SOLDIER4_H__
