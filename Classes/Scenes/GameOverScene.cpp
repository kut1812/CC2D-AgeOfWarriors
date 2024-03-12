#include "GameOverScene.h"
#include "Scenes/MainMenuScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* GameOverScene::create(std::string result)
{
    GameOverScene* scene = new GameOverScene();
    if (scene && scene->init(result))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool GameOverScene::init(std::string result)
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto background = Sprite::create("Background/Background-Screen-03.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(visibleSize.width / background->getContentSize().width);
    this->addChild(background);

    auto background1 = Sprite::create("Background/Upgrade_popUp_box.png");
    background1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background1);

    Chess* chess = Chess::createChess("Assassin5");
    chess->setPosition(Vec2(visibleSize.width *0.38, visibleSize.height *0.5));
    this->addChild(chess);
    chess->setScale(visibleSize.height/ chess->getContentSize().height*0.5);
    chess->setFlippedX(-1);
    chess->stopAllActions();
    AnimationUtils::loadSpriteFrameCache("Animation/", "Assassin5_walk");
    auto aniWalk = AnimationUtils::createAnimation("Assassin5_walk", 99, 0.1f);
    Animate* animate_Walk1 = Animate::create(aniWalk);

    AnimationUtils::loadSpriteFrameCache("Animation/", "Assassin5_attack");
    auto aniAttack = AnimationUtils::createAnimation("Assassin5_attack", 99, 0.1f);
    Animate* animate_Attack1 = Animate::create(aniAttack);

    AnimationUtils::loadSpriteFrameCache("Animation/", "Assassin5_die");
    auto aniDie = AnimationUtils::createAnimation("Assassin5_die", 99, 0.1f);
    Animate* animate_Die1 = Animate::create(aniDie);
    animate_Walk1->retain();
    animate_Attack1->retain();
    animate_Die1->retain();
    Sequence* sequence = Sequence::create(animate_Walk1->clone(), animate_Attack1->clone(), animate_Die1->clone(), nullptr);
    RepeatForever* repeat = RepeatForever::create(sequence);

    chess->runAction(repeat);

    _result = result;
    if (_result=="win")
    {
        auto labelTitle = Label::createWithTTF("VICTORY", "fonts/KnightWarrior.otf", 72);
        //labelTitle->setTextColor(Color4B::BLACK);
        labelTitle->setScale(visibleSize.height / labelTitle->getContentSize().height * 0.2);
        labelTitle->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.8));
        this->addChild(labelTitle, 5);

        auto Arena_icon1 = Sprite::create("Icon/Arena_icon.png");
        Arena_icon1->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.5));
        Arena_icon1->setScale(visibleSize.height / Arena_icon1->getContentSize().height * 0.25);
        this->addChild(Arena_icon1);

        CCLOG("win");
    }
    else if(_result =="lose")
    {
        auto labelTitle = Label::createWithTTF("DEFENSE", "fonts/KnightWarrior.otf", 72);
        //labelTitle->setTextColor(Color4B::BLACK);
        labelTitle->setScale(visibleSize.height / labelTitle->getContentSize().height * 0.2);
        labelTitle->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.8));
        this->addChild(labelTitle, 5);

        auto Heroes_icon1 = Sprite::create("Icon/Heroes_icon.png");
        Heroes_icon1->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.5));
        Heroes_icon1->setScale(visibleSize.height / Heroes_icon1->getContentSize().height * 0.25);
        this->addChild(Heroes_icon1);

        CCLOG("lose");
    }

    std::string buttonOrange = "Button/Orange_btn.png";
    std::string buttonGreen2 = "Button/Green_Btn2.png";

    auto buttonRestart = ui::Button::create(buttonGreen2, buttonOrange);
    buttonRestart->addTouchEventListener(
        [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(GameScene::create());
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }});
    auto labelRestart = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 36);
    labelRestart->setPosition(Vec2(visibleSize.width *0.51, visibleSize.height * 0.3));
    labelRestart->setScale(visibleSize.height / labelRestart->getContentSize().height * 0.05);
    this->addChild(labelRestart, 6);
    buttonRestart->setPosition(labelRestart->getPosition());
    buttonRestart->setScale(visibleSize.height / buttonRestart->getContentSize().height / 8.2);
    this->addChild(buttonRestart, 5);
    
    auto buttonExit = ui::Button::create(buttonGreen2, buttonOrange);
    buttonExit->addTouchEventListener(
        [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(MainMenuScene::createScene());
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }});
    auto labelExit = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 36);
    labelExit->setPosition(Vec2(visibleSize.width *0.66, visibleSize.height * 0.3));
    labelExit->setScale(visibleSize.height / labelExit->getContentSize().height * 0.05);
    this->addChild(labelExit, 6);
    buttonExit->setPosition(labelExit->getPosition());
    buttonExit->setScale(visibleSize.height / buttonExit->getContentSize().height / 8.2);
    this->addChild(buttonExit, 5);

    return true;
}

