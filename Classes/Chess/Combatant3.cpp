#include "Combatant3.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Combatant3* Combatant3::create() {
    auto newObject = new Combatant3();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Combatant3::init()
{
    if (!Sprite::initWithFile("Demo_character/Combatant3.png"))
    {
        return false;
    }
    addData("Combatant3");
    addAnimation("Combatant3");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
