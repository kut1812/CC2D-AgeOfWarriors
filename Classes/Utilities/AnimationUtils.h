#ifndef __ANIMATION_UTILS__
#define __ANIMATION_UTILS__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtils
{
public:
	static Animation* createAnimation(std::string name, int numFrame, float duration);

	static std::pair<Animation*, int> createAnimation(std::string name, float duration);//ko khai bao tien to ben file .h, visual studio buil dc nhung platform khac loi

	static bool loadSpriteFrameCache(std::string path, std::string fileName);
};

#endif // !__ANIMATION_UTILS__
