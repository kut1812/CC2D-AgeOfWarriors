#ifndef __COMBATANT3_H__
#define __COMBATANT3_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Combatant3 : public Chess
{
public:
	static Combatant3* create();
	virtual bool init();
};

#endif // !__COMBATANT3_H__
