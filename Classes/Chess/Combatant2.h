#ifndef __COMBATANT2_H__
#define __COMBATANT2_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Combatant2 : public Chess
{
public:
	static Combatant2* create();
	virtual bool init();
};

#endif // !__COMBATANT2_H__
