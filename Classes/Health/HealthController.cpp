#include "HealthController.h"

HealthController* HealthController::create(int maxHealth, std::string fillPath)
{
	auto newObject = new HealthController();
	if (newObject != nullptr && newObject->init(maxHealth, fillPath))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool HealthController::init(int maxHealth, std::string fillPath)
{
	if (!Sprite::initWithFile(fillPath))
	{
		return false;
	}

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);

	this->_maxHealth = maxHealth;
	this->_currentHealth = maxHealth;

	return true;
}

void HealthController::setCurrentHealth(int newVal)
{
	_currentHealth = newVal;
	this->onChangeCurrent(_currentHealth);
}

int HealthController::getCurrentHealth()
{
	return _currentHealth;
}

void HealthController::setMaxHealth(int newVal)
{
	_maxHealth = newVal;
}

int HealthController::getMaxHealth()
{
	return _maxHealth;
}

void HealthController::onChangeCurrent(int newVal)
{
	if (newVal <= 0)
	{
		return;
	}

	this->setScaleX((float)_currentHealth / _maxHealth);
}