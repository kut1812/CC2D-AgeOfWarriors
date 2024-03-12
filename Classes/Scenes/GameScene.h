#ifndef  __GAME_SCENE_H__
#define  __GAME_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
class ChessSpawn;
class EnemySpawn;
class GameScene :public cocos2d::Scene
{
public:
	bool init() override;
	bool OnContactBegan(cocos2d::PhysicsContact& contact);
	CREATE_FUNC(GameScene);
	void setBackGround(std::string level) { background->setTexture("Background/" + level + "st_Backgound.png"); }
	void setLevel(int level) { _level = level; }
	int getLevel() { return _level; }
	std::string getLevelString() { return std::to_string(_level); }
	void setGold(int Gold) { gold = Gold; setGoldLabel(getGoldString()); }
	void setGoldLabel(std::string gold) { goldLabel->setString(gold); }
	int getGold() { return gold; }
	std::string getGoldString() { return std::to_string(gold); }
	void setExp(int Exp) { exp = Exp; setExpLabel(getExpString()); }
	void setExpLabel(std::string exp) { expLabel->setString(exp); }
	int getExp() { return exp; }
	std::string getExpString() { return std::to_string(exp); }
	int getPriceChess(std::string tyleChess);
	void setArrow(int arrow) { _arrow = arrow; }
	int getArrow() { return _arrow; }
	void scheduleSkillArrow(float dt);
	void createCountDownButton(ui::Button* button,float *cooldown);
	void createSkillButton();

	ChessSpawn* characterSpawn;
	EnemySpawn* enemy;
protected:
	Sprite* background;

	int _level = 1;
	int gold = 50;
	int exp = 0;
	Label* goldLabel ;
	Label* expLabel ;
	Label* levelUpLabel ;
	Label* DefenseArcherLabel ;

	ui::Button* buttonChessSoldier;
	ui::Button* buttonChessArcher;
	ui::Button* buttonChessAssassin;
	ui::Button* buttonChessCombatant;
	ui::Button* buttonDefenseArcher;
	ui::Button* buttonSkill;
	Label* SoldierLabel ;
	Label* ArcherLabel ;
	Label* AssassinLabel ;
	Label* CombatantLabel ;
	cocos2d::Layer* layer;
	Label* speedLabel;
	int speedMultiplier = 1;
	float _countDownSoldier ;
	float _countDownArcher ;
	float _countDownAssassin ;
	float _countDownCombatant ;
	float _countDownSkill ;
	int _arrow=0;
protected:
	void LevelUp();
	void update(float dt) override;
	void updateSpeedLabel(int multiplier);

	void skillArrow();
	void skillScaleChess();
	void skillSpawn();
	void skillPoison();
	void skillFreez();
	void useSkill(int levelSkill);
};
#endif // __GAME_SCENE_H__

