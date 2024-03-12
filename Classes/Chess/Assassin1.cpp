#include "Assassin1.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Assassin1* Assassin1::create() {
    auto newObject = new Assassin1();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Assassin1::init()
{
    if (!Sprite::initWithFile("Demo_character/Assassin1.png"))
    {
        return false;
    }
    addData("Assassin1");
    addAnimation("Assassin1");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
