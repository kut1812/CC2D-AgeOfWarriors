#include "Combatant2.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Combatant2* Combatant2::create() {
    auto newObject = new Combatant2();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Combatant2::init()
{
    if (!Sprite::initWithFile("Demo_character/Combatant2.png"))
    {
        return false;
    }
    addData("Combatant2");
    addAnimation("Combatant2");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
