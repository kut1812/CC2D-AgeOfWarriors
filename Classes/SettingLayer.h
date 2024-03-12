#ifndef  __SETTING_LAYER_H__
#define  __SETTING_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class SettingLayer : public cocos2d::Layer {
public:
	/*static cocos2d::Scene* createScene();*/
	virtual bool init() override;
	CREATE_FUNC(SettingLayer);
};

#endif // __SETTING_LAYER_H__

