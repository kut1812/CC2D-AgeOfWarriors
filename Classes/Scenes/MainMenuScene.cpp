#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "Audio/AudioManager.h"
#include "HowToPlay.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	AudioManager* audioManager = AudioManager::getInstance();
	audioManager->playMusic("mainMenuMusic.mp3");
	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(MainMenuScene::onKeyPressed, this);
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto background = Sprite::create("Background/backgroundMainMenu.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.height/background->getContentSize().height);
	this->addChild(background);

	auto Heroes_icon1 = Sprite::create("Icon/Heroes_icon.png");
	Heroes_icon1->setPosition(Vec2(visibleSize.width *0.25, visibleSize.height *0.5));
	Heroes_icon1->setScale(visibleSize.height / Heroes_icon1->getContentSize().height * 0.1);
	this->addChild(Heroes_icon1);

	auto Heroes_icon2 = Sprite::create("Icon/Heroes_icon.png");
	Heroes_icon2->setPosition(Vec2(visibleSize.width *0.75, visibleSize.height * 0.5));
	Heroes_icon2->setScale(visibleSize.height / Heroes_icon2->getContentSize().height * 0.1);
	this->addChild(Heroes_icon2);

	auto Arena_icon1 = Sprite::create("Icon/Arena_icon.png");
	Arena_icon1->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height *0.4));
	Arena_icon1->setScale(visibleSize.height / Arena_icon1->getContentSize().height * 0.1);
	this->addChild(Arena_icon1);

	auto Arena_icon2 = Sprite::create("Icon/Arena_icon.png");
	Arena_icon2->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.4));
	Arena_icon2->setScale(visibleSize.height / Arena_icon2->getContentSize().height * 0.1);
	this->addChild(Arena_icon2);

	auto Party_box = Sprite::create("Button/Party_box.png");
	Party_box->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35));
	Party_box->setScale(visibleSize.height / Party_box->getContentSize().height * 0.7);
	this->addChild(Party_box,4);

	//auto label = Label::createWithTTF("Press Tab to Game Scene", "fonts/Marker Felt.ttf", 72);
	//label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.9));
	//this->addChild(label);

	////button2->setTitleText("");
	////button2->setTitleColor(Color3B::BLACK); 

	auto labelTitle = Label::createWithTTF("Age Of Warriors", "fonts/VTCS.ttf", 72);
	labelTitle->setTextColor(Color4B::BLACK);
	labelTitle->setScale(visibleSize.height / labelTitle->getContentSize().height * 0.1);
	labelTitle->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height * 0.8));
	this->addChild(labelTitle, 5);

	std::string buttonOrange = "Button/Orange_btn.png";
	std::string buttonGreen2 = "Button/Green_Btn2.png";
	auto buttonStartGame = ui::Button::create(buttonGreen2, buttonOrange);
	buttonStartGame->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	auto labelStartGame = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 36);
	labelStartGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55));
	labelStartGame->setScale(visibleSize.height / labelStartGame->getContentSize().height *0.05);
	this->addChild(labelStartGame,6);
	buttonStartGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.55));
	buttonStartGame->setScale(visibleSize.height / buttonStartGame->getContentSize().height/8.2);
	this->addChild(buttonStartGame, 5);

	auto buttonTutorial = ui::Button::create(buttonGreen2, buttonOrange);
	buttonTutorial->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, HowToPlay::create()));
				//Director::getInstance()->replaceScene(TransitionFade::create(2, SettingsScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	auto labelTutorial = Label::createWithTTF("How to play", "fonts/Marker Felt.ttf", 36);
	labelTutorial->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
	labelTutorial->setScale(visibleSize.height / labelStartGame->getContentSize().height * 0.05);
	this->addChild(labelTutorial, 6);
	buttonTutorial->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
	buttonTutorial->setScale(visibleSize.height / buttonTutorial->getContentSize().height / 8.2);
	this->addChild(buttonTutorial, 5);

	//auto buttonHighScores = ui::Button::create(buttonGreen2, buttonOrange);
	//buttonHighScores->addTouchEventListener(
	//	[&](Ref* sender, ui::Widget::TouchEventType type) {
	//		switch (type)
	//		{
	//		case ui::Widget::TouchEventType::BEGAN:
	//			break;
	//		case ui::Widget::TouchEventType::ENDED:
	//			Director::getInstance()->replaceScene(TransitionFade::create(2, HowToPlay::create()));
	//			break;
	//		case ui::Widget::TouchEventType::CANCELED:
	//			break;
	//		default:
	//			break;
	//		}});
	//auto labelHighScores = Label::createWithTTF("High Scores", "fonts/Marker Felt.ttf", 36);
	//labelHighScores->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
	//labelHighScores->setScale(visibleSize.height / labelStartGame->getContentSize().height * 0.05);
	//this->addChild(labelHighScores, 6);
	//buttonHighScores->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
	//buttonHighScores->setScale(visibleSize.height / buttonHighScores->getContentSize().height / 8.2);
	//this->addChild(buttonHighScores, 5);

	auto buttonExit = ui::Button::create(buttonGreen2, buttonOrange);
	buttonExit->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->end();
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	auto labelExit = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 36);
	labelExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
	labelExit->setScale(visibleSize.height / labelStartGame->getContentSize().height * 0.05);
	this->addChild(labelExit, 6);
	buttonExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
	buttonExit->setScale(visibleSize.height / buttonExit->getContentSize().height / 8.2);
	this->addChild(buttonExit, 5);

	auto checkboxMusic = cocos2d::ui::CheckBox::create("EmptyChecklist_box.png",
		"CheckList.png");

	if (audioManager->getMusicVolume() <= 0)
	{
		checkboxMusic->setSelected(false);
	}
	else
	{
		checkboxMusic->setSelected(true);
	}
	checkboxMusic->setPosition(Vec2(visibleSize.width * 0.450, visibleSize.height * 0.12));
	checkboxMusic->addEventListener([&](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
		AudioManager* audioManager = AudioManager::getInstance();
		switch (type)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			audioManager->setMusicVolume(0.5f);
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			audioManager->setMusicVolume(0.0f);
			break;
		default:
			break;
		}
		});
	this->addChild(checkboxMusic,5);
	auto labelMusic = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 36);
	labelMusic->setPosition(Vec2(visibleSize.width * 0.45, visibleSize.height * 0.05));
	labelMusic->setScale(visibleSize.height / labelMusic->getContentSize().height * 0.05);
	this->addChild(labelMusic, 6);

	auto checkboxSFX = cocos2d::ui::CheckBox::create("EmptyChecklist_box.png",
		"CheckList.png");

	if (audioManager->getSFXVolume() <= 0)
	{
		checkboxSFX->setSelected(false);
	}
	else
	{
		checkboxSFX->setSelected(true);
	}
	checkboxSFX->setPosition(Vec2(visibleSize.width * 0.55, visibleSize.height * 0.12));
	checkboxSFX->addEventListener([&](Ref* sender, cocos2d::ui::CheckBox::EventType type) {
		AudioManager* audioManager = AudioManager::getInstance();
		switch (type)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			audioManager->setSFXVolume(0.5f);
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			audioManager->setSFXVolume(0.0f);
			break;
		default:
			break;
		}
		});
	this->addChild(checkboxSFX,5);
	auto labelSFX = Label::createWithTTF("SFX", "fonts/Marker Felt.ttf", 36);
	labelSFX->setPosition(Vec2(visibleSize.width * 0.55, visibleSize.height * 0.05));
	labelSFX->setScale(visibleSize.height / labelSFX->getContentSize().height * 0.05);
	this->addChild(labelSFX, 6);

	return true;
}
void MainMenuScene::onKeyPressed(EventKeyboard::KeyCode key, Event* ev) {
	if (key==EventKeyboard::KeyCode::KEY_TAB)
	{
		auto gameScene = GameScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(2, gameScene));
	}
}