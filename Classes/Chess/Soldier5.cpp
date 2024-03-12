#include "Soldier5.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;


Soldier5* Soldier5::create() {
    auto newObject = new Soldier5();
    if (newObject != nullptr &&  newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Soldier5::init()
{
    if (!Sprite::initWithFile("Demo_character/Soldier55.png"))
    {
        return false;
    }
    addData("Soldier5");
    addAnimation("Soldier5");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}


