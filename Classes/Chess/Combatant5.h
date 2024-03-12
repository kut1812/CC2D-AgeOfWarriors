#ifndef __COMBATANT5_H__
#define __COMBATANT5_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Combatant5 : public Chess
{
public:
	static Combatant5* create();
	virtual bool init();
};

#endif // !__COMBATANT5_H__
