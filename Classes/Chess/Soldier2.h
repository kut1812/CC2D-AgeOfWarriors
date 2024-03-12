#ifndef __SOLDIER2_H__
#define __SOLDIER2_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class Soldier2 : public Chess
{
public:
	static Soldier2* create();
	virtual bool init();
	
};

#endif // !__SOLDIER2_H__
