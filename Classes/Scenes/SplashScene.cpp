#include "SplashScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SplashScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("HelloWorld.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(1.0f);
	this->addChild(background);

	auto label = Label::createWithTTF("YOUR GAME NAME", "fonts/Marker Felt.ttf", 36);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label);

	//auto label1 = Label::create();
	//label1->setString("Label Default Value");
	//label1->setPosition(Vec2(visibleSize.width / 2, 50));
	//label1->enableShadow();
	//label1->enableOutline(Color4B::GREEN, 1);
	//label1->enableGlow(Color4B::YELLOW);
	//this->addChild(label1);

	//auto labelSytemFont = Label::createWithSystemFont("Label with System Font", "Aria", 30);
	//labelSytemFont->setScale(3.0f);
	//labelSytemFont->setPosition(Vec2(visibleSize.width / 2, 100));
	//labelSytemFont->enableShadow();
	//labelSytemFont->enableOutline(Color4B::GREEN, 50);
	//labelSytemFont->enableGlow(Color4B::YELLOW);
	//this->addChild(labelSytemFont);

	auto moveBy = MoveBy::create(1.5, Vec2(0, -200));
	auto callFunc = CallFunc::create([&]() {
		auto mainMenuScene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(2, mainMenuScene));
		});
	auto sequence = Sequence::create(moveBy, callFunc, nullptr);
	label->runAction(sequence);
	return true;
}