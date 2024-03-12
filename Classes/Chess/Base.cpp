#include "Base.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Base* Base::create() {
    auto newObject = new Base();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Base::init()
{
    if (!Sprite::initWithFile("Barrack/Lvl1_ori.png"))
    {
        return false;
    }
    setHealth(5000);
    return true;
}

void Base::setIMG()
{
    if (percentHP==100 && percentHP>80)
    {
        this->setTexture("Barrack/Lvl" + getLevelString() + "_ori.png");
    }
    else if( percentHP<=80 && percentHP > 60)
    {
        this->setTexture("Barrack/Lvl" + getLevelString() + "_broken1.png");

    }
    else if( percentHP<=60 && percentHP > 40)
    {
        this->setTexture("Barrack/Lvl" + getLevelString() + "_broken2.png");
    }
    else if( percentHP<=40 && percentHP > 20)
    {
        this->setTexture("Barrack/Lvl" + getLevelString() + "_broken3.png");
    }
    else if( percentHP<=20)
    {
        this->setTexture("Barrack/Lvl" + getLevelString() + "_broken4.png");
    }
}

void Base::update(float dt)
{
    Chess::update(dt);
    if (percentHP - ((float)getHealth()/5000*100) >= 20)
    {
        percentHP -= 20;
        setIMG();
    }
}

