#include "Combatant5.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Combatant5* Combatant5::create() {
    auto newObject = new Combatant5();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Combatant5::init()
{
    if (!Sprite::initWithFile("Demo_character/Combatant5.png"))
    {
        return false;
    }
    addData("Combatant5");
    addAnimation("Combatant5");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
