#ifndef __HEALTH_CONTROLLER_H__
#define __HEALTH_CONTROLLER_H__

#include "cocos2d.h"
USING_NS_CC;

class HealthController : public Sprite
{
public:
	static HealthController* create(int current, std::string fillPath);
	bool init(int current, std::string fillPath);

	void setCurrentHealth(int newVal);
	int getCurrentHealth();

	void setMaxHealth(int newVal);
	int getMaxHealth();
private:
	int _currentHealth, _maxHealth;
	void onChangeCurrent(int newVal);
};

#endif // !__HEALTH_CONTROLLER_H__