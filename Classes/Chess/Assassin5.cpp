#include "Assassin5.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Assassin5* Assassin5::create() {
    auto newObject = new Assassin5();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Assassin5::init()
{
    if (!Sprite::initWithFile("Demo_character/Assassin5.png"))
    {
        return false;
    }
    addData("Assassin5");
    addAnimation("Assassin5");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
