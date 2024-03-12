#include "Combatant4.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Combatant4* Combatant4::create() {
    auto newObject = new Combatant4();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}


bool Combatant4::init()
{
    if (!Sprite::initWithFile("Demo_character/Combatant4.png"))
    {
        return false;
    }
    addData("Combatant4");
    addAnimation("Combatant4");
    runActionWalk();
    this->scheduleUpdate();

    return true;
}
