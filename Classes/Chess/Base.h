#ifndef __BASE_H__
#define __BASE_H__

#include "cocos2d.h"
#include "Chess.h"
#include "Utilities/AnimationUtils.h"

USING_NS_CC;

class GameScene;
class Base : public Chess
{
public:
	static Base* create();
	virtual bool init();
	void setLevel(int level) { _level = level; setIMG(); }
	std::string getLevelString() { return std::to_string(_level); }
private:
	void setIMG();

	void update(float dt);
	float percentHP=100;
	int _level=1;
};

#endif // !__BASE_H__
