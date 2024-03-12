#include "Soldier1.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;


Soldier1* Soldier1::create() {
    auto newObject = new Soldier1();
    if (newObject != nullptr &&  newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Soldier1::init()
{
    if (!Sprite::initWithFile("Demo_character/Soldier1.png"))
    {
        return false;
    }
    addData("Soldier1");
    addAnimation("Soldier1");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
