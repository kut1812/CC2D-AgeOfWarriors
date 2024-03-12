#ifndef __SOLDIER5_H__
#define __SOLDIER5_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class Soldier5 : public Chess
{
public:
	static Soldier5* create();
	virtual bool init();
};

#endif // !__SOLDIER5_H__
