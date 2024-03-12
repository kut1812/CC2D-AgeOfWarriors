#include "Archer1.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Archer1* Archer1::create() {
    auto newObject = new Archer1();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Archer1::init()
{
    if (!Sprite::initWithFile("Demo_character/Archer1.png"))
    {
        return false;
    }
    addData("Archer1");
    addAnimation("Archer1");

    runActionWalk();
    this->scheduleUpdate();

    return true;
}
