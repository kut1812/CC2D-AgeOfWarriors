#include "Assassin3.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Assassin3* Assassin3::create() {
    auto newObject = new Assassin3();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Assassin3::init()
{
    if (!Sprite::initWithFile("Demo_character/Assassin3.png"))
    {
        return false;
    }
    addData("Assassin3");
    addAnimation("Assassin3");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
