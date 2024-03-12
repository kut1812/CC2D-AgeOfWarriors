#include "Combatant1.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Combatant1* Combatant1::create() {
    auto newObject = new Combatant1();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Combatant1::init()
{
    if (!Sprite::initWithFile("Demo_character/Combatant1.png"))
    {
        return false;
    }
    addData("Combatant1");
    addAnimation("Combatant1");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
