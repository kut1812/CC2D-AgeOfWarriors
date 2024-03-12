#ifndef __COMBATANT1_H__
#define __COMBATANT1_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Combatant1 : public Chess
{
public:
	static Combatant1* create();
	virtual bool init();
};

#endif // !__COMBATANT1_H__
