#include "Assassin2.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Assassin2* Assassin2::create() {
    auto newObject = new Assassin2();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Assassin2::init()
{
    if (!Sprite::initWithFile("Demo_character/Assassin2.png"))
    {
        return false;
    }
    addData("Assassin2");
    addAnimation("Assassin2");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
