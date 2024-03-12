#include "Archer4.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Archer4* Archer4::create() {
    auto newObject = new Archer4();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Archer4::init()
{
    if (!Sprite::initWithFile("Demo_character/Archer4.png"))
    {
        return false;
    }
    addData("Archer4");
    addAnimation("Archer4");

    runActionWalk();
    this->scheduleUpdate();

    return true;
}
