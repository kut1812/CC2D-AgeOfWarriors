#ifndef  __GAME_OVER_SCENE_H__
#define  __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create(std::string result);
    virtual bool init(std::string result);

private:
    std::string _result;
};

#endif // __GAME_OVER_SCENE_H__