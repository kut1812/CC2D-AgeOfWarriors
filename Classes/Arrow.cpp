#include "Arrow.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;

Arrow* Arrow::create() {
    auto newObject = new Arrow();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Arrow::init()
{
    if (!Sprite::initWithFile("SkillArrow.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    setDame(50);
    this->setPosition(Vec2(visibleSize.width * 0.06, visibleSize.height * 0.43));
    this->setFlippedX(-1);
    Vec2 basePosition = Vec2(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.45));
    auto move = MoveTo::create(1, basePosition);
    PhysicsBody* physics = PhysicsBody::createBox(this->getContentSize() );
    physics->setDynamic(false);
    physics->setCategoryBitmask(DefineBitmask::Skill);
    physics->setContactTestBitmask(DefineBitmask::Enemy);
    physics->setCollisionBitmask(DefineBitmask::Enemy);
    this->addComponent(physics);
    this->runAction(move);

    return true;
}

