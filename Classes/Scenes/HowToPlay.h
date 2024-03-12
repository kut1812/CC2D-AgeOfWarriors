#ifndef  __HOW_TO_PLAY_SCENE_H__
#define  __HOW_TO_PLAY_SCENE_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
class HowToPlay : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create();
    virtual bool init();

private:
};

#endif // __HOW_TO_PLAY_SCENE_H__