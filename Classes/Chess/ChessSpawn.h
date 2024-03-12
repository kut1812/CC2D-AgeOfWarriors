#ifndef __CHESS_SPAWN_H__
#define __CHESS_SPAWN_H__

#include "cocos2d.h"
#include "Chess/Chess.h"
#include "Chess/Soldier1.h"
#include "Chess/Archer1.h"
#include "Chess/Assassin1.h"
#include "Chess/Combatant1.h"
#include "Chess/Soldier5.h"
#include "Chess/Combatant5.h"
#include "Chess/Base.h"

USING_NS_CC;
class GameScene;
class ChessSpawn : public Node {
public:
    static ChessSpawn* create(GameScene* scene);
    bool init(GameScene* scene); 
    bool spawnCharacter(std::string tyleChess);
    void addPhysics(Chess* chess);
    void spawnDefenseArcher(std::string tyleChess);
    cocos2d::Vector<Chess*> characters;
    void setSprites(cocos2d::Vector<Chess*> *sprites);
    void setAction();
    void setLevelDefenseArcher(int level) { levelDefenseArcher = level; }
    int getLevelDefenseArcher() { return levelDefenseArcher; }
    std::string getLevelDefenseArcherString() { return std::to_string(levelDefenseArcher); }
    void update(float dt);
    Base* getBase() { return yourBase; }
private:
    int levelDefenseArcher=0;
    GameScene* _scene;
    Base* yourBase;
    Chess* DefenseArcher=nullptr;
    cocos2d::Vector<Chess*>* _sprites;
    int count;
};

#endif // !__CHESS_SPAWN_H__
