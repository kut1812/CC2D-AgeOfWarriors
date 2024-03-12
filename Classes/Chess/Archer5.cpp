#include "Archer5.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Archer5* Archer5::create() {
    auto newObject = new Archer5();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Archer5::init()
{
    if (!Sprite::initWithFile("Demo_character/Archer5.png"))
    {
        return false;
    }
    addData("Archer5");
    addAnimation("Archer5");

    runActionWalk();
    this->scheduleUpdate();

    return true;
}
