#include "SettingsScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* SettingsScene::createScene()
{
	return SettingsScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SettingsScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto background = Sprite::create("background.png");
	//background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//background->setScale(0.8f);
	//this->addChild(background);

	//auto label = Label::createWithTTF("Settings Scene", "fonts/Marker Felt.ttf", 36);
	//label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.8));
	//this->addChild(label);


	//auto buttonQuit = ui::Button::create("QuitGreen.png", "QuitRed.png");
	//buttonQuit->addTouchEventListener(
	//	[&](Ref* sender, ui::Widget::TouchEventType type) {
	//		switch (type)
	//		{
	//		case ui::Widget::TouchEventType::BEGAN:
	//			break;
	//		case ui::Widget::TouchEventType::ENDED:
	//			Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
	//			break;
	//		case ui::Widget::TouchEventType::CANCELED:
	//			break;
	//		default:
	//			break;
	//		}});
	//buttonQuit->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	//this->addChild(buttonQuit);

	//auto slider = ui::Slider::create("Blank 192x48.png","CloseSelected.png");
	//slider->loadProgressBarTexture("Blank.png");
	//slider->setPosition(visibleSize / 2);
	//addChild(slider);
	//slider->addEventListener([](Ref* sender, ui::Slider::EventType tyle) {
	//	auto slider = dynamic_cast<ui::Slider*>(sender);
	//	if (tyle==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	//	{
	//		CCLOG("%d", slider->getPercent());
	//	}
	//	});
	int id = AudioEngine::play2d("Audio/die.mp3", true, 1.0f);
	auto slider1 = ui::Slider::create("loadingbar/Background Static.png", "CloseNormal.png");
	slider1->loadProgressBarTexture("loadingbar/Foreground.png");
	slider1->setPercent(100);
	slider1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.6));
	addChild(slider1);
	slider1->addEventListener([=](Ref* sender, ui::Slider::EventType type) {

		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			auto slidermusic = dynamic_cast<ui::Slider*>(sender);
			log("music percent: %d", id);
			AudioEngine::setVolume(id, (float)slidermusic->getPercent()/100);
		}
		});

	return true;
}