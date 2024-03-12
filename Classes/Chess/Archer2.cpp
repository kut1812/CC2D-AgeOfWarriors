#include "Archer2.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Archer2* Archer2::create() {
    auto newObject = new Archer2();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Archer2::init()
{
    if (!Sprite::initWithFile("Demo_character/Archer2.png"))
    {
        return false;
    }
    addData("Archer2");
    addAnimation("Archer2");

    runActionWalk();
    this->scheduleUpdate();

    return true;
}
