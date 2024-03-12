#include "Archer3.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Archer3* Archer3::create() {
    auto newObject = new Archer3();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Archer3::init()
{
    if (!Sprite::initWithFile("Demo_character/Archer3.png"))
    {
        return false;
    }
    addData("Archer3");
    addAnimation("Archer3");

    runActionWalk();
    this->scheduleUpdate();

    return true;
}
