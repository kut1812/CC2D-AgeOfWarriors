#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class GameScene;
class Arrow : public Chess
{
public:
	static Arrow* create();
	virtual bool init();
private:
};

#endif // !__ARROW_H__
