#include "Chess.h"
#include "Scenes/GameScene.h"
#include "Chess/Base.h"
#include "Chess/Soldier1.h"
#include "Chess/Archer1.h"
#include "Chess/Assassin1.h"
#include "Chess/Combatant1.h"
#include "Chess/Soldier2.h"
#include "Chess/Archer2.h"
#include "Chess/Assassin2.h"
#include "Chess/Combatant2.h"
#include "Chess/Soldier3.h"
#include "Chess/Archer3.h"
#include "Chess/Assassin3.h"
#include "Chess/Combatant3.h"
#include "Chess/Soldier4.h"
#include "Chess/Archer4.h"
#include "Chess/Assassin4.h"
#include "Chess/Combatant4.h"
#include "Chess/Soldier5.h"
#include "Chess/Archer5.h"
#include "Chess/Assassin5.h"
#include "Chess/Combatant5.h"
#include "Arrow.h"
#include "DefineBitmask.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

Chess* Chess::create() {
    auto newObject = new Chess();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}
bool Chess::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    this->scheduleUpdate();
}

void Chess::addData(std::string tyleChess)
{
    rapidjson::Document docs;

    std::string dataContent = FileUtils::getInstance()->getStringFromFile("Data/"+tyleChess+".json");
    docs.Parse(dataContent.c_str());

    setPrice(docs["_price"].GetInt());
    setHealth(docs["_healthChess"].GetInt());
    setDame(docs["_damageChess"].GetInt());
    setAttackSpeed(docs["_attackSpeed"].GetFloat());
    setSpeed(docs["_speedChess"].GetFloat());
    setFightFar(docs["_fightFar"].GetBool());
    setCountDown(getAttackSpeed());
    return;
}

void Chess::addAnimation(std::string tyleChess)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess+"_walk");
    auto aniWalk = AnimationUtils::createAnimation(tyleChess + "_walk", 99, 0.1f);
    aniWalk->setDelayPerUnit(1.0f / aniWalk->getFrames().size());
    Animate* animate_Walk = Animate::create(aniWalk);
    animateWalk = RepeatForever::create(animate_Walk);

    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess + "_attack");
    auto aniAttack = AnimationUtils::createAnimation(tyleChess + "_attack", 99, 0.1f);
    aniAttack->setDelayPerUnit(getAttackSpeed() / aniAttack->getFrames().size());
    Animate* animate_Attack = Animate::create(aniAttack);
    animateAttack = RepeatForever::create(animate_Attack);

    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess+"_die");
    auto aniDie = AnimationUtils::createAnimation(tyleChess + "_die", 99, 0.1f);
    //aniDie->setDelayPerUnit(2.0f / aniDie->getFrames().size());
    animateDie = Animate::create(aniDie);

    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess + "_poisoned");
    auto aniPoisoned = AnimationUtils::createAnimation(tyleChess + "_poisoned", 99, 0.1f);
    aniPoisoned->setDelayPerUnit(1.0f / aniPoisoned->getFrames().size());
    Animate* animate_Poisoned = Animate::create(aniPoisoned);
    animatePoisoned = RepeatForever::create(animate_Poisoned);

    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess + "_freez");
    auto aniFreez = AnimationUtils::createAnimation(tyleChess + "_freez", 99, 0.1f);
    aniFreez->setDelayPerUnit(1.0f / aniFreez->getFrames().size());
    Animate* animate_Freez = Animate::create(aniFreez);
    animateFreez = RepeatForever::create(animate_Freez);

    animateWalk->retain();
    animateAttack->retain();
    animateDie->retain();
    animatePoisoned->retain();
    animateFreez->retain();
}

void Chess::addAnimationIdle(std::string tyleChess)
{
    AnimationUtils::loadSpriteFrameCache("Animation/", tyleChess + "_idle");
    auto aniIdle = AnimationUtils::createAnimation(tyleChess + "_idle", 99, 0.1f);
    //aniDie->setDelayPerUnit(2.0f / aniDie->getFrames().size());
    Animate* animate_Idle = Animate::create(aniIdle);
    animateIdle = RepeatForever::create(animate_Idle);

    animateIdle->retain();

}

Chess* Chess::createChess(std::string tyleChess)
{
    Chess* chess= nullptr;
    if (tyleChess=="Soldier1")
    {
        chess = Soldier1::create();
    }
    else if (tyleChess=="Archer1")
    {
        chess = Archer1::create();
    }
    else if (tyleChess=="Assassin1")
    {
        chess = Assassin1::create();
    }
    else if (tyleChess=="Combatant1")
    {
        chess = Combatant1::create();
    }
    if (tyleChess=="Soldier2")
    {
        chess = Soldier2::create();
    }
    else if (tyleChess=="Archer2")
    {
        chess = Archer2::create();
    }
    else if (tyleChess=="Assassin2")
    {
        chess = Assassin2::create();
    }
    else if (tyleChess=="Combatant2")
    {
        chess = Combatant2::create();
    }
    if (tyleChess=="Soldier3")
    {
        chess = Soldier3::create();
    }
    else if (tyleChess=="Archer3")
    {
        chess = Archer3::create();
    }
    else if (tyleChess=="Assassin3")
    {
        chess = Assassin3::create();
    }
    else if (tyleChess=="Combatant3")
    {
        chess = Combatant3::create();
    }
    if (tyleChess=="Soldier4")
    {
        chess = Soldier4::create();
    }
    else if (tyleChess=="Archer4")
    {
        chess = Archer4::create();
    }
    else if (tyleChess=="Assassin4")
    {
        chess = Assassin4::create();
    }
    else if (tyleChess=="Combatant4")
    {
        chess = Combatant4::create();
    }
    if (tyleChess=="Soldier5")
    {
        chess = Soldier5::create();
    }
    else if (tyleChess=="Soldier5Special")
    {
        chess = Soldier5::create();
        chess->setPrice(0);
        chess->setHealth(1500);
        chess->setDame(100);
        chess->setScale(2);
        chess->setAnchorPoint(Vec2(0.5, 0.29));
    }
    else if (tyleChess=="Soldier5Skill")
    {
        chess = Soldier5::create();
        chess->setPrice(0);
    }
    else if (tyleChess=="Archer5")
    {
        chess = Archer5::create();
    }
    else if (tyleChess=="Assassin5")
    {
        chess = Assassin5::create();
    }
    else if (tyleChess=="Combatant5")
    {
        chess = Combatant5::create();
    }
    return chess;
}

void Chess::attack(Chess* chess)
{
    if (getCountDown()<=0)
    {
        chess->takeDame(getDame());
        if (dynamic_cast<Base*>(chess)==nullptr)
        {
            auto color = cocos2d::Color3B::RED;
            chess->showDamage(color,std::to_string(getDame()));
        }
        _countDown = getAttackSpeed();
    }
}

void Chess::takeDame(int dame)
{
    setHealth(getHealth() - dame);
    _healthCtrl->setCurrentHealth(getHealth());
    auto color = cocos2d::Color3B::RED;
    if (getPoisoned()==true)
    {
        color = cocos2d::Color3B(128, 0, 128);
    }
    showDamage(color, std::to_string(dame));
}

void Chess::showDamage(cocos2d::Color3B &color,const std::string& damageText)
{
    auto damageLabel = cocos2d::Label::createWithTTF(damageText, "fonts/KnightWarrior.otf", 24);
    damageLabel->setColor(color);
    damageLabel->setPosition(Vec2(this->getPosition().x*0.1,this->getPosition().y*0.1));
    if (this&&this->getPhysicsBody()!=nullptr)
    {
  if (this->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Character)
    {
        damageLabel->setScaleX(-1);
    }
    }
  
    this->addChild(damageLabel);

    auto moveUp = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(0, 50));
    auto fadeOut = cocos2d::FadeOut::create(1.0f);
    auto remove = cocos2d::CallFunc::create([=]() {
        damageLabel->removeAllChildrenWithCleanup(true);
        });
    auto sequence = cocos2d::Sequence::create(cocos2d::Spawn::create(moveUp, fadeOut, nullptr), remove, nullptr);

    damageLabel->runAction(sequence);
}

void Chess::showGold(const std::string& goldText)
{
    auto goldLabel = cocos2d::Label::createWithTTF(goldText, "fonts/KnightWarrior.otf", 24);
    goldLabel->setColor(cocos2d::Color3B::YELLOW); 
    goldLabel->setPosition(Vec2(this->getPosition().x * 0.1, this->getPosition().y * 0.1));
    if (this && this->getPhysicsBody() != nullptr)
    {
if (this->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Character)
    {
        goldLabel->setScaleX(-1);
    }
    }
    
    this->addChild(goldLabel);

    auto moveUp = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(0, 50));
    auto fadeOut = cocos2d::FadeOut::create(1.0f);
    auto remove = cocos2d::CallFunc::create([=]() {
        goldLabel->removeAllChildrenWithCleanup(true);
        });
    auto sequence = cocos2d::Sequence::create(cocos2d::Spawn::create(moveUp, fadeOut, nullptr), remove, nullptr);

    goldLabel->runAction(sequence);
}

void Chess::onEnter()
{
    Node::onEnter();

    // health
    _healthCtrl = HealthController::create(getHealth(), "health_green.png");
    if (dynamic_cast<Soldier5*>(this)!=nullptr || dynamic_cast<Combatant5*>(this) != nullptr)
    {
        _healthCtrl->setPosition(Vec2(this->getContentSize().width * 1.3
            , this->getContentSize().height) * 0.9);
    }
    else
    {
        _healthCtrl->setPosition(Vec2(this->getContentSize().width*0.92
        , this->getContentSize().height)*0.7);
    }
    if (this!=nullptr)
    {
 if (this->getPhysicsBody()!=nullptr)
    {
        if (this->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Enemy)
        {
            this->setTextureHealth("health_red.png");
        }
        if (this->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Skill)
        {
            _healthCtrl->setVisible(false);
        }
    }
    else
    {
        _healthCtrl->setVisible(false);
    }
    }
   
    
    this->addChild(_healthCtrl);
    if (dynamic_cast<Base*>(this)!=nullptr)
    {
        _healthCtrl->setVisible(false);
    }
}

void Chess::update(float dt)
{
    if (_countDown>0)
    {
        _countDown -= dt;
    }
    if (getPoisoned() == true) {
        // Giảm 5 điểm máu mỗi giây
        if (_countDownPoisoned <= 0) {
            takeDame(5);
            _countDownPoisoned = 1.0f;
        }
        else {
            _countDownPoisoned -= dt;
        }
    }
    if (getHealth()<0)
    {
        if (dynamic_cast<Base*>(this)!=nullptr)
        {
            if (this->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Enemy) {
                Director::getInstance()->replaceScene( GameOverScene::create("win"));
            }
            else
            {
                Director::getInstance()->replaceScene( GameOverScene::create("lose"));
            }
        }
        setState("die");

    }
}

