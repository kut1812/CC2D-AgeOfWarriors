#include "Soldier2.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;


Soldier2* Soldier2::create() {
    auto newObject = new Soldier2();
    if (newObject != nullptr &&  newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Soldier2::init()
{
    if (!Sprite::initWithFile("Demo_character/Soldier2.png"))
    {
        return false;
    }
    addData("Soldier2");
    addAnimation("Soldier2");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
