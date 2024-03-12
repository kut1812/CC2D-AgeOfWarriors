#ifndef __SOLDIER1_H__
#define __SOLDIER1_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class Soldier1 : public Chess
{
public:
	static Soldier1* create();
	virtual bool init();
	
};

#endif // !__SOLDIER1_H__
