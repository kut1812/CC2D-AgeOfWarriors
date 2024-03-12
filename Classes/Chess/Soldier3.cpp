#include "Soldier3.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
USING_NS_CC;


Soldier3* Soldier3::create() {
    auto newObject = new Soldier3();
    if (newObject != nullptr &&  newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Soldier3::init()
{
    if (!Sprite::initWithFile("Demo_character/Soldier3.png"))
    {
        return false;
    }
    addData("Soldier3");
    addAnimation("Soldier3");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
