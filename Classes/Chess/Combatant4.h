#ifndef __COMBATANT4_H__
#define __COMBATANT4_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"
USING_NS_CC;

class Combatant4 : public Chess
{
public:
	static Combatant4* create();
	virtual bool init();
};

#endif // !__COMBATANT4_H__
