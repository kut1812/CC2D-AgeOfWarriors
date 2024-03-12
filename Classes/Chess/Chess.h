#ifndef __CHESS_H__
#define __CHESS_H__

#include "cocos2d.h"
#include "Scenes/GameScene.h"
#include "Utilities/AnimationUtils.h"
#include "Health/HealthController.h"
#include "Scenes/GameOverScene.h"

/*
#include "Chess/Soldier1.h"
#include "Chess/Archer1.h"
#include "Chess/Assassin1.h"
#include "Chess/Combatant1.h"*/

USING_NS_CC;
class Soldier1;
class Archer1;
class Assassin1;
class Combatant1;
class Chess : public Sprite 
{
public:
	static Chess* create();
	virtual bool init();
	void addData(std::string tyleChess);
	void addAnimation(std::string tyleChess);
	void addAnimationIdle(std::string tyleChess);
	static Chess* createChess(std::string tyleChess);
	void attack(Chess* chess);
	void takeDame(int dame);

	void update(float dt);
public:
	std::string getCurrentState() { return _currentState; }
	void setCurrentState(std::string currentState) { _currentState=currentState; }
	void runActionWalk() { this->runAction(animateWalk->clone()); }
	void runActionAttack() { this->runAction(animateAttack->clone()); }
	void runActionDie() { this->runAction(animateDie->clone()); }
	void runActionIdle() { this->runAction(animateIdle->clone()); }
	void runActionPoisoned() { this->runAction(animatePoisoned->clone()); }
	void runActionFreez() { this->runAction(animateFreez->clone()); }
	Animate* getActionDie() { return animateDie->clone(); }
	void setPrice(int price) { _price = price; }
	int getPrice() { return _price; }
	void setHealth(int health) { _healthChess=health; }
	int getHealth() { return _healthChess; }
	void setDame(int dame) { _damageChess =dame; }
	int getDame() { return _damageChess; }
	void setAttackSpeed(float atsp) { _attackSpeed =atsp; }
	float getAttackSpeed() { return _attackSpeed; }
	void setSpeed(float speed) { _speedChess=speed; }
	float getSpeed() { return _speedChess; }
	void setFightFar(bool x) { _fightFar = x; }
	bool getFightFar() { return _fightFar; }
	void setPoisoned(bool x) { _isPoisoned = x; }
	bool getPoisoned() { return _isPoisoned; }
	void setFeezing(bool x) { _isFeezing = x; }
	bool getFeezing() { return _isFeezing; }
	void setCountDown(float cd) { _countDown =cd; }
	float getCountDown() { return _countDown; }
	std::string getState() { return _state; }
	void setState(std::string state) { _state=state; }
	bool getColliding() { return _colliding; }
	void setColliding(bool x) { _colliding=x; }
	bool getCollidingBase() { return _collidingBase; }
	void setCollidingBase(bool x) { _collidingBase =x; }
	void showDamage(cocos2d::Color3B& color,const std::string& damageText);
	void showGold(const std::string& goldText);
	HealthController* getHealthController() { return _healthCtrl; }
	void setTextureHealth(std::string fillPath) { _healthCtrl->setTexture(fillPath); }
private:
	void onEnter();

	HealthController* _healthCtrl;
	int _price;
	int _healthChess;
	int _damageChess;
	float _attackSpeed;
	float _speedChess;
	bool _fightFar;
	float _countDown;
	bool _colliding=false;
	bool _collidingBase=false;
	bool _isPoisoned =false;
	bool _isFeezing =false;
	float _countDownPoisoned = 1.0f;
	
	std::string _state;
	RepeatForever* animateWalk;
	RepeatForever* animateAttack;
	RepeatForever* animateIdle;
	RepeatForever* animatePoisoned;
	RepeatForever* animateFreez;
	Animate* animateDie;
	std::string _currentState;
};

#endif // !__CHESS_H__
