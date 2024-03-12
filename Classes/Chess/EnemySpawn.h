#ifndef __ENEMY_SPAWN_H__
#define __ENEMY_SPAWN_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Chess/Soldier5.h"
#include "Chess/Combatant5.h"
#include "Chess/Base.h"

USING_NS_CC;

class GameScene;
class EnemySpawn : public Node
{
public:
	static EnemySpawn* create(GameScene* scene);
	virtual bool init(GameScene* scene);
	void startSpawn();
	cocos2d::Vector<Chess*> enemies;
	void setSprites(cocos2d::Vector<Chess*> *sprites);
	cocos2d::Vector<Chess*>* _sprites;
	void setAction();
	void update(float dt);

	void setLevel(int level) { _level = level; }
	int getLevel() { return _level; }
	std::string getLevelString() { return std::to_string(_level); }
private:
	void spawnEnemy(std::string tyleChess);
	void addPhysics(Chess* chess);
	void spawnDefenseArcher(std::string tyleChess);
	void LevelUp();

	int _level=1;
	int soldierCount;
	int archerCount;
	int assassinCount;
	int combatantCount;
	int spawnTimer;
	bool isFirstWave;
	int count;

	GameScene* _scene;
	Base* enemyBase;
	Chess* DefenseArcher;
};

#endif // !__ENEMY_SPAWN_H__
