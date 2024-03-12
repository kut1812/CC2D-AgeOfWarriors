#include "Soldier4.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;


Soldier4* Soldier4::create() {
    auto newObject = new Soldier4();
    if (newObject != nullptr &&  newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Soldier4::init()
{
    if (!Sprite::initWithFile("Demo_character/Soldier4.png"))
    {
        return false;
    }
    addData("Soldier4");
    addAnimation("Soldier4");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
