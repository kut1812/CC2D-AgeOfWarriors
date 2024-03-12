#include "Assassin4.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Assassin4* Assassin4::create() {
    auto newObject = new Assassin4();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Assassin4::init()
{
    if (!Sprite::initWithFile("Demo_character/Assassin4.png"))
    {
        return false;
    }
    addData("Assassin4");
    addAnimation("Assassin4");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
