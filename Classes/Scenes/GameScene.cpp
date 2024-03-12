#include "GameScene.h"
#include "MainMenuScene.h"
#include "SettingLayer.h"
#include "ui/CocosGUI.h"
#include "DefineBitmask.h"
#include "Chess/ChessSpawn.h"
#include "Chess/EnemySpawn.h"
#include "Chess/Base.h"
#include "Audio/AudioManager.h"
#include "Arrow.h"
USING_NS_CC;

bool GameScene::init() {
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	AudioManager* audioManager = AudioManager::getInstance();
	audioManager->playMusic("backgroundMusic.mp3");

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	layer = Layer::create();
	background = Sprite::create("Background/"+getLevelString()+"st_Backgound.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.6));
	background->setScale(visibleSize.height / background->getContentSize().height);
	this->addChild(background);
	this->addChild(layer,100);

	auto bgLayerDown = Sprite::create("Background/Btn_orange_active.png");
	layer->addChild(bgLayerDown);
	bgLayerDown->setAnchorPoint(Vec2(0.5, 0));
	bgLayerDown->setScaleY(visibleSize.height / bgLayerDown->getContentSize().height*0.2);
	bgLayerDown->setScaleX(visibleSize.width / bgLayerDown->getContentSize().width );
	bgLayerDown->setPosition(Vec2(visibleSize.width  / 2, visibleSize.height*0));

	auto vs = Sprite::create("Vs.png");
	vs->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.7));
	vs->setScale(0.8);
	this->addChild(vs);

	auto goldBar = Sprite::create("GoldBar.png");
	goldBar->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	goldBar->setScale(visibleSize.height / goldBar->getContentSize().height * 0.1);
	this->addChild(goldBar);

	goldLabel = Label::createWithTTF(""+getGoldString(), "fonts/KnightWarrior.otf", 36);
	goldLabel->setColor(Color3B::YELLOW);
	goldLabel->setPosition(goldBar->getPosition()); 
	this->addChild(goldLabel);
	
	auto expBar = Sprite::create("ExpBar.png");
	expBar->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.9));
	expBar->setScale(visibleSize.height / goldBar->getContentSize().height * 0.1);
	this->addChild(expBar);

	expLabel = Label::createWithTTF(""+getExpString(), "fonts/KnightWarrior.otf", 36);
	expLabel->setColor(Color3B(0,0,200));
	expLabel->setPosition(expBar->getPosition());
	this->addChild(expLabel);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	buttonChessSoldier = ui::Button::create("Icon/Soldier" + getLevelString() + ".png", "Icon/Soldier" + getLevelString() + ".png");
	buttonChessSoldier->setPosition(Vec2(visibleSize.width * 0.05, visibleSize.height * 0.125));
	buttonChessSoldier->setScale(visibleSize.height / buttonChessSoldier->getContentSize().height * 0.15);
	layer->addChild(buttonChessSoldier);
	buttonChessSoldier->setTag(3);
	buttonChessSoldier->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				if (_countDownSoldier<=0)
				{
					if (characterSpawn->spawnCharacter("Soldier" + getLevelString()))
					{
						_countDownSoldier = buttonChessSoldier->getTag();
						createCountDownButton(buttonChessSoldier, &_countDownSoldier);
					}
				}
				break;
			}
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	SoldierLabel = Label::createWithTTF(std::to_string(getPriceChess("Soldier"+getLevelString())), "fonts/KnightWarrior.otf", 36);
	SoldierLabel->setPosition(Vec2(visibleSize.width * 0.05, visibleSize.height * 0.03));
	SoldierLabel->setColor(Color3B::YELLOW);
	layer->addChild(SoldierLabel);

	buttonChessArcher = ui::Button::create("Icon/Archer"+getLevelString()+".png", "Icon/Archer" + getLevelString() + ".png");
	buttonChessArcher->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				if (_countDownArcher<=0)
				{
					if (characterSpawn->spawnCharacter("Archer" + getLevelString()))
					{
						_countDownArcher = buttonChessArcher->getTag();
						createCountDownButton(buttonChessArcher, &_countDownArcher);
					}
				}
				break;
			}
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonChessArcher->setPosition(Vec2(visibleSize.width * 0.15, visibleSize.height * 0.125));
	buttonChessArcher->setScale(visibleSize.height / buttonChessArcher->getContentSize().height * 0.15);
	layer->addChild(buttonChessArcher);
	buttonChessArcher->setTag(3);

	ArcherLabel = Label::createWithTTF(std::to_string(getPriceChess("Archer" + getLevelString())), "fonts/KnightWarrior.otf", 36);
	ArcherLabel->setPosition(Vec2(visibleSize.width * 0.15, visibleSize.height * 0.03));
	ArcherLabel->setColor(Color3B::YELLOW);
	layer->addChild(ArcherLabel);

	buttonChessAssassin = ui::Button::create("Icon/Assassin" + getLevelString() + ".png", "Icon/Assassin" + getLevelString() + ".png");
	buttonChessAssassin->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				if (_countDownAssassin<=0)
				{
					if (characterSpawn->spawnCharacter("Assassin" + getLevelString()))
					{
						_countDownAssassin = buttonChessAssassin->getTag();
						createCountDownButton(buttonChessAssassin, &_countDownAssassin);
					}
				}
				break;
			}
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonChessAssassin->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.125));
	buttonChessAssassin->setScale(visibleSize.height / buttonChessAssassin->getContentSize().height * 0.15);
	layer->addChild(buttonChessAssassin);
	buttonChessAssassin->setTag(4);

	AssassinLabel = Label::createWithTTF(std::to_string(getPriceChess("Assassin" + getLevelString())), "fonts/KnightWarrior.otf", 36);
	AssassinLabel->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.03));
	AssassinLabel->setColor(Color3B::YELLOW);
	layer->addChild(AssassinLabel);

	buttonChessCombatant = ui::Button::create("Icon/Combatant" + getLevelString() + ".png", "Icon/Combatant" + getLevelString() + ".png");
	buttonChessCombatant->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				if (_countDownCombatant<=0)
				{
					if (characterSpawn->spawnCharacter("Combatant" + getLevelString()))
					{
						_countDownCombatant = buttonChessCombatant->getTag();
						createCountDownButton(buttonChessCombatant, &_countDownCombatant);
					}
				}
				break;
			}
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonChessCombatant->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.125));
	buttonChessCombatant->setScale(visibleSize.height / buttonChessCombatant->getContentSize().height * 0.15);
	layer->addChild(buttonChessCombatant);
	buttonChessCombatant->setTag(5);

	CombatantLabel = Label::createWithTTF(std::to_string(getPriceChess("Combatant" + getLevelString())), "fonts/KnightWarrior.otf", 36);
	CombatantLabel->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.03));
	CombatantLabel->setColor(Color3B::YELLOW);
	layer->addChild(CombatantLabel);

	auto buttonSetting = ui::Button::create("Button/Option_icon.png");
	buttonSetting->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				Director::getInstance()->pause();
				auto layer1 = SettingLayer::create();
				this->addChild(layer1,101);
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonSetting->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.9));
	buttonSetting->setScale(visibleSize.height / buttonSetting->getContentSize().height * 0.10);
	layer->addChild(buttonSetting, 99);
	
	auto buttonLevelUp = ui::Button::create("Icon/LevelUp.png","Icon/LevelUp.png");
	buttonLevelUp->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				if (getLevel()<5)
				{
					auto priceLevelUp = (getLevel() - 1) * 50 + 200;
					if (getExp() > priceLevelUp) {
						LevelUp();
						setExp(getExp() - priceLevelUp);
						if (getLevel()==5)
						{
							levelUpLabel->setString("200");
							buttonLevelUp->loadTextures("Icon/Soldier5Special.png", "Icon/Soldier5Special.png");
							buttonLevelUp->setScale(visibleSize.height / buttonLevelUp->getContentSize().height * 0.15);
						}
					}
				}
				else
				{
					if (getExp() >= 200) {
						setExp(getExp() - 200);
						characterSpawn->spawnCharacter("Soldier5Special");
					}
				}
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonLevelUp->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.125));
	buttonLevelUp->setScale(visibleSize.height / buttonLevelUp->getContentSize().height * 0.15);
	layer->addChild(buttonLevelUp, 99);

	levelUpLabel = Label::createWithTTF(std::to_string(200 + ((getLevel() - 1) * 50)), "fonts/KnightWarrior.otf", 36);
	levelUpLabel->setColor(Color3B(0, 0, 200));
	levelUpLabel->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.03));
	layer->addChild(levelUpLabel);

	buttonDefenseArcher = ui::Button::create("Icon/DefenseArcher"+getLevelString() + ".png", "Icon/DefenseArcher" + getLevelString() + ".png");
	buttonDefenseArcher->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				CCLOG("%d", getLevel());
				if (getLevel() > characterSpawn->getLevelDefenseArcher() && getGold() > 30 + (5 * (getLevel() - 1)))
				{
					audioManager->playSFX("clickCommodity.mp3");
					setGold(getGold() - (30 + (5 * (getLevel() - 1))));
					characterSpawn->spawnDefenseArcher("Archer" + getLevelString());
					characterSpawn->setLevelDefenseArcher(characterSpawn->getLevelDefenseArcher()+1);
				}
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonDefenseArcher->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.125));
	buttonDefenseArcher->setScale(visibleSize.height / buttonDefenseArcher->getContentSize().height * 0.15);
	layer->addChild(buttonDefenseArcher, 99);

	DefenseArcherLabel = Label::createWithTTF(std::to_string(30 + (5 * (getLevel() - 1))), "fonts/KnightWarrior.otf", 36);
	DefenseArcherLabel->setColor(Color3B::YELLOW);
	DefenseArcherLabel->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.03));
	layer->addChild(DefenseArcherLabel);

	//skill
	buttonSkill = ui::Button::create("Icon/Skill (" + getLevelString() + ").png", "Icon/Skill (" + getLevelString() + ").png" );
	buttonSkill->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				if (_countDownSkill<=0)
				{
					_countDownSkill = buttonSkill->getTag();
					createCountDownButton(buttonSkill, &_countDownSkill);
					useSkill(getLevel());
				}
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonSkill->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.125));
	buttonSkill->setScale(visibleSize.height / buttonSkill->getContentSize().height * 0.15);
	buttonSkill->setTag(20);
	layer->addChild(buttonSkill, 99);

	//speed Game
	speedLabel = Label::createWithTTF("x1", "fonts/KnightWarrior.otf", 36);
	speedLabel->setTextColor(Color4B::GRAY);
	speedLabel->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.9));
	auto speedButton = ui::Button::create("Button/Speed.png", "Button/speed.png");
	speedButton->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.9));
	speedButton->setScale(1.5f);
	this->addChild(speedButton);
	this->addChild(speedLabel);

	speedButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED:
			speedMultiplier += 1;
			if (speedMultiplier > 3) {
				speedMultiplier = 1; 
			}
			updateSpeedLabel( speedMultiplier); 
			break;
		default:
			break;
		}
		});

	// character spawn
	characterSpawn = ChessSpawn::create(this);
	this->addChild(characterSpawn);

	// enemy spawn
	enemy = EnemySpawn::create(this);
	this->addChild(enemy);
	enemy->setSprites(&characterSpawn->characters);
	characterSpawn->setSprites(&enemy->enemies);
	enemy->startSpawn();
	this->scheduleUpdate();
	
	layer->setPosition(this->getDefaultCamera()->getPosition()+ visibleSize / -2);
	this->schedule([=](float dt) {
		this->scheduleSkillArrow(dt);
		}, 1.0f, "skill_arrow_schedule");
	return true;
}

void GameScene::scheduleSkillArrow(float dt) {
	skillArrow();
}

bool GameScene::OnContactBegan(cocos2d::PhysicsContact& contact)
{
	
	auto chessA = dynamic_cast<Chess*>(contact.getShapeA()->getBody()->getNode());
	auto chessB = dynamic_cast<Chess*>(contact.getShapeB()->getBody()->getNode());
	PhysicsBody* bodyA;
	PhysicsBody* bodyB;
	if (chessA && chessA->getPhysicsBody() && chessB && chessB->getPhysicsBody()) {
		bodyA = chessA->getPhysicsBody();
		bodyB = chessB->getPhysicsBody();
		if (bodyA->getCategoryBitmask() == DefineBitmask::Character && bodyB->getCategoryBitmask() == DefineBitmask::Enemy ||
			bodyB->getCategoryBitmask() == DefineBitmask::Character && bodyA->getCategoryBitmask() == DefineBitmask::Enemy)
		{
			if (chessA->getState()!="poisoned" && chessA->getState()!="freez")
			{
			chessA->setState("attack");
			}
			else if (chessA->getFeezing()==true||chessA->getPoisoned()==true)
			{
				chessA->setCurrentState("attack");
			}
			chessA->setColliding(true);
			if (chessB->getState()!="poisoned" && chessB->getState() != "freez")
			{
			chessB->setState("attack");
			}
			else if (chessB->getFeezing()==true||chessB->getPoisoned() == true)
			{
				chessB->setCurrentState("attack");
			}
			chessB->setColliding(true);
			if (dynamic_cast<Base*>(chessA) != nullptr)
			{
				chessB->setCollidingBase(true);
			}
			if (dynamic_cast<Base*>(chessB) != nullptr)
			{
				chessA->setCollidingBase(true);
			}
		}
		else if (bodyB->getCategoryBitmask() == DefineBitmask::Skill && bodyA->getCategoryBitmask() == DefineBitmask::Enemy)
		{
			chessA->takeDame(chessB->getDame());
			chessB->removeFromParentAndCleanup(true);
		}
		else if (bodyA->getCategoryBitmask() == DefineBitmask::Skill && bodyB->getCategoryBitmask() == DefineBitmask::Enemy)
		{
			chessB->takeDame(chessA->getDame());
			chessA->removeFromParentAndCleanup(true);
		}
	}
	
	return true;
}

int GameScene::getPriceChess(std::string tyleChess)
{
	auto chess = Chess::createChess(tyleChess);
	return chess->getPrice();
}

void GameScene::createCountDownButton(ui::Button* button, float* cooldown)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto coolDown = ui::LoadingBar::create("Icon/cooldown.png");
	coolDown->setScale(visibleSize.height / button->getContentSize().height * 0.15);
	coolDown->setPosition(button->getPosition());
	layer->addChild(coolDown,100);
	coolDown->setDirection(ui::LoadingBar::Direction::LEFT);
	coolDown->setRotation(-90);
	coolDown->setPercent(100);
	coolDown->schedule([=](float delta) {
		coolDown->setPercent((float)*cooldown/button->getTag()*100);
		if (coolDown->getPercent() <= 0)
		{
			coolDown->removeFromParentAndCleanup(true);
		}
		}, "updateCooldown");
}

void GameScene::LevelUp()
{
	setLevel(getLevel() + 1);
	buttonChessSoldier->loadTextures("Icon/Soldier" + getLevelString() + ".png", "Icon/Soldier" + getLevelString() + ".png");
	buttonChessArcher->loadTextures("Icon/Archer" + getLevelString() + ".png", "Icon/Archer" + getLevelString() + ".png");
	buttonChessAssassin->loadTextures("Icon/Assassin" + getLevelString() + ".png", "Icon/Assassin" + getLevelString() + ".png");
	buttonChessCombatant->loadTextures("Icon/Combatant" + getLevelString() + ".png", "Icon/Combatant" + getLevelString() + ".png");
	buttonDefenseArcher->loadTextures("Icon/DefenseArcher" + getLevelString() + ".png","Icon/DefenseArcher" + getLevelString() + ".png");
	buttonSkill->loadTextures("Icon/Skill (" + getLevelString() + ").png", "Icon/Skill (" + getLevelString() + ").png" + getLevelString() + ".png");
	SoldierLabel->setString(std::to_string(getPriceChess("Soldier" + getLevelString())));
	ArcherLabel->setString(std::to_string(getPriceChess("Archer" + getLevelString())));
	AssassinLabel->setString(std::to_string(getPriceChess("Assassin" + getLevelString())));
	CombatantLabel->setString(std::to_string(getPriceChess("Combatant" + getLevelString())));
	levelUpLabel->setString(std::to_string(200 + ((getLevel() - 1) * 50)));
	DefenseArcherLabel->setString(std::to_string(30 + (5 * (getLevel() - 1))));
	setBackGround(getLevelString());
	characterSpawn->getBase()->setLevel(getLevel());
}

void GameScene::skillArrow()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (getArrow()>0)
	{
		setArrow(getArrow() - 1);
		auto arrow = Arrow::create();
		addChild(arrow);
	}
}

void GameScene::skillScaleChess()
{
	for (auto& sprite : characterSpawn->characters) {
		if (dynamic_cast<Base*>(sprite) == nullptr) {
			auto scaleTo = ScaleTo::create(2, -1.4, 1.4);
			sprite->runAction(scaleTo);
			sprite->setHealth( sprite->getHealthController()->getMaxHealth()/2+sprite->getHealth());
			sprite->getHealthController()->setMaxHealth(sprite->getHealthController()->getMaxHealth() * 1.5);
			sprite->setDame(sprite->getDame() * 1.5);
		}
	}
}

void GameScene::skillSpawn()
{
	characterSpawn->spawnCharacter("Soldier5Skill");
}

void GameScene::skillPoison()
{
	for (auto& sprite : enemy->enemies) {
		if (dynamic_cast<Base*>(sprite) == nullptr && sprite->getState()!="die") {
			sprite->setState("poisoned");
		}
	}
}

void GameScene::useSkill(int levelSkill)
{
	float duration = 0.1f;
	float magnitude = 5.0f;

	auto moveUp = cocos2d::MoveBy::create(duration, cocos2d::Vec2(0, magnitude));
	auto moveDown = cocos2d::MoveBy::create(duration, cocos2d::Vec2(0, -magnitude));
	auto moveRight = cocos2d::MoveBy::create(duration, cocos2d::Vec2(magnitude, 0));
	auto moveLeft = cocos2d::MoveBy::create(duration, cocos2d::Vec2(-magnitude, 0));

	auto sequence = cocos2d::Sequence::create(moveUp, moveDown, moveRight, moveLeft, nullptr);

	if (levelSkill==1)
	{
		setArrow(3);
	}
	else if (levelSkill == 2)
	{
		skillScaleChess();
	}
	else if (levelSkill ==3 )
	{
		skillSpawn();
	}
	else if (levelSkill ==4 )
	{
		skillPoison();
	}
	else if (levelSkill == 5)
	{
		skillFreez();
		cocos2d::Director::getInstance()->getRunningScene()->runAction(sequence);
	}
	cocos2d::Device::vibrate(0.5f);
}

void GameScene::skillFreez()
{
	AudioManager* audioManager = AudioManager::getInstance();
	for (auto& sprite : enemy->enemies) {
		if (dynamic_cast<Base*>(sprite) == nullptr && sprite->getState() != "die") {
			sprite->setState("freez");
		}
	}
	audioManager->playSFX("cloverCyclone.mp3");
}

void GameScene::update(float dt) {	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (_countDownSoldier>0)
	{
		_countDownSoldier -= dt;
	}
	if (_countDownArcher > 0)
	{
		_countDownArcher -= dt;
	}
	if (_countDownAssassin > 0)
	{
		_countDownAssassin -= dt;
	}
	if (_countDownCombatant > 0)
	{
		_countDownCombatant -= dt;
	}
	if (_countDownSkill > 0)
	{
		_countDownSkill -= dt;
	}
}

void GameScene::updateSpeedLabel(int multiplier)
{
	std::string speedText = "x" + std::to_string(multiplier);
	speedLabel->setString(speedText);

	Director::getInstance()->getScheduler()->setTimeScale(multiplier * 0.3 + 0.7);
}
