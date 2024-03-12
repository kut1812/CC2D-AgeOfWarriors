#include "SettingLayer.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "ui/CocosGUI.h"
#include "Audio/AudioManager.h"

USING_NS_CC;
//
//Scene* SettingLayer::createScene()
//{
//	return SettingLayer::create();
//}

bool SettingLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	AudioManager* audioManager = AudioManager::getInstance();

	auto background = Sprite::create("Options_box.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.height / background->getContentSize().height * 0.8);
	this->addChild(background);

	std::string buttonOrange = "Button/Orange_btn.png";
	std::string buttonGreen2 = "Button/Green_Btn2.png";
	auto buttonResume = ui::Button::create(buttonGreen2, buttonOrange);
	buttonResume->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->resume();
				this->removeFromParentAndCleanup(true);
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonResume->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.65));
	buttonResume->setScale(visibleSize.height / buttonResume->getContentSize().height * 0.15);
	this->addChild(buttonResume, 5);
	auto labelResume = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 36);
	labelResume->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.65));
	labelResume->setScale(visibleSize.height / labelResume->getContentSize().height * 0.05);
	this->addChild(labelResume, 6);

	auto buttonRestart = ui::Button::create(buttonGreen2, buttonOrange);
	buttonRestart->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->resume();
				Director::getInstance()->replaceScene(GameScene::create());
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonRestart->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.45));
	buttonRestart->setScale(visibleSize.height / buttonRestart->getContentSize().height * 0.15);
	this->addChild(buttonRestart, 5);
	auto labelRestart = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 36);
	labelRestart->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.45));
	labelRestart->setScale(visibleSize.height / labelRestart->getContentSize().height * 0.05);
	this->addChild(labelRestart, 6);

	auto buttonQuit = ui::Button::create(buttonGreen2, buttonOrange);
	buttonQuit->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->resume();
				this->removeFromParentAndCleanup(true);
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonQuit->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.25));
	buttonQuit->setScale(visibleSize.height / buttonQuit->getContentSize().height * 0.15);
	this->addChild(buttonQuit, 5);
	auto labelQuit = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 36);
	labelQuit->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.25));
	labelQuit->setScale(visibleSize.height / labelQuit->getContentSize().height * 0.05);
	this->addChild(labelQuit, 6);
	
	auto checkboxMusic = cocos2d::ui::CheckBox::create("EmptyChecklist_box.png",
		"CheckList.png");
	
	if (audioManager->getMusicVolume()<=0)
	{
		checkboxMusic->setSelected(false);
	}
	else
	{
		checkboxMusic->setSelected(true);
	}
	checkboxMusic->setPosition(Vec2(visibleSize.width * 0.50, visibleSize.height * 0.65));
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
	this->addChild(checkboxMusic);
	auto labelMusic = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 36);
	labelMusic->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.58));
	labelMusic->setScale(visibleSize.height / labelMusic->getContentSize().height * 0.05);
	this->addChild(labelMusic, 6);

	auto checkboxSFX = cocos2d::ui::CheckBox::create("EmptyChecklist_box.png",
		"CheckList.png");
	
	if (audioManager->getSFXVolume()<=0)
	{
		checkboxSFX->setSelected(false);
	}
	else
	{
		checkboxSFX->setSelected(true);
	}
	checkboxSFX->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.65));
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
	this->addChild(checkboxSFX);
	auto labelSFX = Label::createWithTTF("SFX", "fonts/Marker Felt.ttf", 36);
	labelSFX->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.58));
	labelSFX->setScale(visibleSize.height / labelSFX->getContentSize().height * 0.05);
	this->addChild(labelSFX, 6);

	
	// Tạo một slider mới
	auto slider = cocos2d::ui::Slider::create();
	// Đặt các thuộc tính cho Slider
	slider->loadBarTexture("Cartoon_RPG_UI_Loading_Bar_-_Background.png"); // thiết lập texture cho thanh track
	slider->loadSlidBallTextures("H.png", "H.png", ""); // thiết lập texture cho nút trượt
	slider->loadProgressBarTexture("Cartoon_RPG_UI_Loading_Bar_-_Fill.png"); // thiết lập texture cho thanh tiến trình
	slider->setPosition(cocos2d::Vec2(visibleSize.width * 0.6, visibleSize.height * 0.45)); // thiết lập vị trí
	slider->setPercent(audioManager->getMusicVolume()*100); // thiết lập phần trăm ban đầu (giá trị từ 0 đến 100)
	slider->setScale(visibleSize.width / slider->getContentSize().width * 0.28);
	this->addChild(slider); // thêm slider vào layer hiện hành

	// Đặt hàm callback khi giá trị của slider thay đổi
	slider->addEventListener([](Ref* sender, cocos2d::ui::Slider::EventType type) {
		AudioManager* audioManager = AudioManager::getInstance();
		int percent = static_cast<cocos2d::ui::Slider*>(sender)->getPercent();
		audioManager->setMusicVolume((float)percent / 100);
		});
	
	// Tạo một slider mới
	auto sliderSFX = cocos2d::ui::Slider::create();
	// Đặt các thuộc tính cho sliderSFX
	sliderSFX->loadBarTexture("Cartoon_RPG_UI_Loading_Bar_-_Background.png"); // thiết lập texture cho thanh track
	sliderSFX->loadSlidBallTextures("H.png", "H.png", ""); // thiết lập texture cho nút trượt
	sliderSFX->loadProgressBarTexture("Cartoon_RPG_UI_Loading_Bar_-_Fill.png"); // thiết lập texture cho thanh tiến trình
	sliderSFX->setPosition(cocos2d::Vec2(visibleSize.width * 0.6, visibleSize.height * 0.25)); // thiết lập vị trí
	sliderSFX->setPercent(audioManager->getSFXVolume()*100); // thiết lập phần trăm ban đầu (giá trị từ 0 đến 100)
	sliderSFX->setScale(visibleSize.width / sliderSFX->getContentSize().width * 0.28);
	this->addChild(sliderSFX); // thêm sliderSFX vào layer hiện hành

	// Đặt hàm callback khi giá trị của sliderSFX thay đổi
	sliderSFX->addEventListener([](Ref* sender, cocos2d::ui::Slider::EventType type) {
		AudioManager* audioManager = AudioManager::getInstance();
		int percent = static_cast<cocos2d::ui::Slider*>(sender)->getPercent();
		audioManager->setSFXVolume((float)percent / 100);
		});
	
	return true;
}

