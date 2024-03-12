#include "ChessSpawn.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
#include "Scenes/GameScene.h"
#include"Audio/AudioManager.h"
ChessSpawn* ChessSpawn::create(GameScene* scene)
{
	auto newObject = new ChessSpawn();
	if (newObject != nullptr && newObject->init(scene)) {

		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool ChessSpawn::init(GameScene* scene) {
	_scene = scene;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	yourBase = Base::create();
	addPhysics(yourBase);
	yourBase->setPosition(Vec2(visibleSize.width * 0.01, visibleSize.height * 0.34));
	yourBase->setScale(visibleSize.height / yourBase->getContentSize().height * 0.2);
	yourBase->setAnchorPoint(Vec2(0, 0));
	_scene->addChild(yourBase, 10);
	characters.pushBack(yourBase);
	
	auto baseBar = ui::LoadingBar::create("Green_Bar.png");
	baseBar->setScale(visibleSize.height / baseBar->getContentSize().height * 0.07);
	baseBar->setPosition(Vec2(visibleSize.width*0.40,visibleSize.height*0.75));
	baseBar->setAnchorPoint(Vec2(1, 0.5));
	_scene->addChild(baseBar, 5);
	baseBar->setDirection(ui::LoadingBar::Direction::RIGHT);
	baseBar->setPercent(100);
	baseBar->schedule([=](float delta) {
		baseBar->setPercent((float)yourBase->getHealth() / yourBase->getHealthController()->getMaxHealth() * 100);
		}, "updateBaseBar");
	auto baseBarBG = Sprite::create("Green_Bar_Bg.png");
	baseBarBG->setPosition(baseBar->getPosition());
	baseBarBG->setScale(visibleSize.height / baseBar->getContentSize().height * 0.07);
	baseBarBG->setAnchorPoint(Vec2(1, 0.5));
	_scene->addChild(baseBarBG,4);

	auto Cs01 = Sprite::create("Cs01.png");
	Cs01->setPosition(baseBar->getPosition());
	Cs01->setScale(  0.8);
	_scene->addChild(Cs01, 6);

	auto PLAYER = Label::createWithTTF("PLAYER", "fonts/KnightWarrior.otf", 36);
	//goldLabel->setColor(Color3B::YELLOW);
	PLAYER->setPosition(Vec2(visibleSize.width * 0.30, visibleSize.height * 0.82));
	_scene->addChild(PLAYER,7);

	this->scheduleUpdate();
	return true;
}

bool ChessSpawn::spawnCharacter(std::string tyleChess)
{
	AudioManager* audioManager = AudioManager::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Chess* chess = Chess::createChess(tyleChess);
	if (chess==nullptr || chess->getPrice()>_scene->getGold() )
	{
		chess->removeFromParentAndCleanup(this);
		return false;
	}
	audioManager->playSFX("clickCommodity.mp3");
	addPhysics(chess);
	chess->setPosition(Vec2(visibleSize.width * 0.05, visibleSize.height * 0.45));
	chess->setState("walk");
	chess->setScaleX(-1);
	if (tyleChess=="Soldier5Special")
	{
		chess->setScaleX(-2);
	}
	_scene->addChild(chess);
	_scene->setGold(_scene->getGold() - chess->getPrice());
	characters.pushBack(chess);
	return true;
}

void ChessSpawn::addPhysics(Chess* chess)
{
	PhysicsBody* physics;
	if (dynamic_cast<Soldier5*>(chess) != nullptr || dynamic_cast<Combatant5*>(chess))
	{
		Vec2 points[] = { Vec2(15, -50), Vec2(100, -50), Vec2(100, 50), Vec2(15, 50) };
		physics = PhysicsBody::createPolygon(points, 4);
	}
	else
	{
		physics = PhysicsBody::createBox(chess->getContentSize() * 0.6);
	}
	physics->setDynamic(false);
	physics->setCategoryBitmask(DefineBitmask::Character);
	physics->setContactTestBitmask(DefineBitmask::Enemy);
	physics->setCollisionBitmask(DefineBitmask::Enemy);
	chess->addComponent(physics);
}

void ChessSpawn::spawnDefenseArcher(std::string tyleChess)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (DefenseArcher != nullptr)
	{
		DefenseArcher->removeFromParentAndCleanup(true);
	}
	DefenseArcher = Chess::createChess(tyleChess);
	DefenseArcher->setDame(_scene->getLevel() * 5 + DefenseArcher->getDame()-5);
	DefenseArcher->addAnimationIdle(tyleChess);
	DefenseArcher->setPosition(Vec2(visibleSize.width * 0.06, visibleSize.height * 0.43));
	DefenseArcher->setScaleX(-1);
	DefenseArcher->setState("idle");
	//DefenseArcher->getHealthController()->setVisible(false);
	_scene->addChild(DefenseArcher, 11);
}

void ChessSpawn::setSprites(cocos2d::Vector<Chess*> *sprites)
{
	_sprites = sprites;
}

void ChessSpawn::setAction() {
	bool firstElement = true;
	AudioManager* audioManager = AudioManager::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto& chess : characters) {
		if (firstElement) {
			firstElement = false;
			continue; 
		}
		if (chess->getState() == "walk") {
			if (chess->getCurrentState() != "walk") {
				chess->stopAllActions();
				chess->runActionWalk();
				Vec2 chessPosition = chess->getPosition();
				Vec2 basePosition = Vec2(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.45));
				float distance = chessPosition.distance(basePosition);
				if (distance != 0)
				{
					auto move = MoveTo::create(distance / chess->getSpeed(), basePosition);
					chess->runAction(move);
				}
				else
				{
					chess->setState("attack");
					for (auto& sprite : *_sprites) {
						sprite->setColliding(true);
						break;
					}
				}
				chess->setCurrentState("walk");
			}
			if (chess->getFightFar())
			{
				for (auto& sprite : *_sprites) {
					if (sprite->getState() != "die" && sprite->getPosition().getDistance(chess->getPosition()) < visibleSize.width / 4)
					{
						chess->setColliding(false);
						chess->setState("attack");
						break;
					}
				}
			}
		}
		else if (chess->getState() == "attack") {
			if (chess->getCurrentState() != "attack") {
				chess->stopAllActions();
				chess->runActionAttack();
				chess->setCurrentState("attack");
				chess->setCountDown(chess->getAttackSpeed());
			}

			auto hasColliding = false;
			if (chess->getFightFar() == false) {
				if (_sprites != nullptr) { // Kiểm tra _sprites có tồn tại không
					for (auto& sprite : *_sprites) {
						if (sprite != nullptr && sprite->getColliding() == true && sprite->getState() != "die") {
							chess->attack(sprite);
							hasColliding = true;
						}
					}
				}
			}
			else {
				Chess* nearestSprite = nullptr;
				float minDistance = std::numeric_limits<float>::max();
				if (_sprites != nullptr) { // Kiểm tra _sprites có tồn tại không
					for (auto& sprite : *_sprites) {
						if (sprite != nullptr) { // Kiểm tra sprite có tồn tại không
							float distance = chess->getPosition().getDistance(sprite->getPosition());
							if (distance < visibleSize.width / 4 && sprite->getState() != "die") {
								if (distance < minDistance) {
									minDistance = distance;
									nearestSprite = sprite;
								}
							}
						}
					}
				}
				if (nearestSprite != nullptr) {
					chess->attack(nearestSprite);
					hasColliding = true;
				}
			}
			if (hasColliding == false) {
				chess->setState("walk");
			}
		}

		else if (chess->getState() == "die") {
			if (chess->getCurrentState() != "die")
			{
				if (chess->getCollidingBase() == true)
				{
					chess->setCollidingBase(false);
					bool hasAttackBase = false;
					for (auto& _chess : characters) {
						if (_chess->getState() != "die" && _chess->getCollidingBase() == true)
						{
							for (auto& base : *_sprites) {
								base->setColliding(true);
								hasAttackBase == true;
								break;
							}
							break;
						}
					}
					if (hasAttackBase==false)
					{
						for (auto& base : *_sprites) {
							base->setColliding(false);
							break;
						}
					}
				}
				audioManager->playSFX("summonerDeath.mp3");
				chess->removeAllChildrenWithCleanup(true);
				chess->setCurrentState("die");
				chess->showGold(std::to_string(chess->getPrice() / 2));
				_scene->setGold(_scene->getGold() + chess->getPrice() / 2);
				chess->stopAllActions();
				chess->removeAllComponents();
				chess->runAction(Sequence::create(
					chess->getActionDie(),
					CallFuncN::create([](Node* sender) {
						sender->removeFromParentAndCleanup(true);
						}),
					nullptr
				));
			}
		}
		else if (chess->getState() == "freez")
		{
			if (chess->getFeezing() != true)
			{
				chess->stopAllActions();
				chess->runActionFreez();
				chess->setFeezing(true);
				std::string countdownName = "freezeCountdown_" + std::to_string(count);
				count += 1;
				this->scheduleOnce([=](float dt) {
					chess->setState(chess->getCurrentState());
					chess->setCurrentState("freez");
					chess->setFeezing(false);
					}, 5.0f, countdownName.c_str());
			}
		}
		else if (chess->getState() == "poisoned")
		{
			if (chess->getPoisoned() != true)
			{
				chess->stopAllActions();
				chess->runActionPoisoned();
				chess->setPoisoned(true);
				std::string countdownName = "poisonedCountdown" + std::to_string(count);
				count += 1;
				this->scheduleOnce([=](float dt) {
					chess->setState(chess->getCurrentState());
					chess->setCurrentState("poisoned");
					}, 1.0f, countdownName.c_str());
			}
			}
	}
	if (DefenseArcher!=nullptr)
	{
		if (DefenseArcher->getState() == "idle")
		{
			if (DefenseArcher->getCurrentState() != "idle")
			{
				DefenseArcher->stopAllActions();
				DefenseArcher->runActionIdle();
				DefenseArcher->setCurrentState("idle");
			}
			for (auto& sprite : *_sprites) {
				if (sprite->getState() != "die" && sprite->getPosition().getDistance(DefenseArcher->getPosition()) < visibleSize.width / 3)
				{
					DefenseArcher->setState("attack");
					break;
				}
			}
		}
		else if (DefenseArcher->getState() == "attack")
		{
			auto hasColliding = false;
			if (DefenseArcher->getCurrentState() != "attack")
			{
				DefenseArcher->stopAllActions();
				DefenseArcher->runActionAttack();
				DefenseArcher->setCurrentState("attack");
				DefenseArcher->setCountDown(DefenseArcher->getAttackSpeed());
			}
			Chess* nearestSprite = nullptr;
			float minDistance = std::numeric_limits<float>::max();
			if (_sprites != nullptr) { // Kiểm tra _sprites có tồn tại không
				for (auto& sprite : *_sprites) {
					if (sprite != nullptr) { // Kiểm tra sprite có tồn tại không
						float distance = DefenseArcher->getPosition().getDistance(sprite->getPosition());
						if (distance < visibleSize.width / 3 && sprite->getState() != "die") {
							if (distance < minDistance) {
								minDistance = distance;
								nearestSprite = sprite;
							}
						}
					}
				}
			}
			if (nearestSprite != nullptr) {
				DefenseArcher->attack(nearestSprite);
				hasColliding = true;
			}
			if (hasColliding == false) {
				DefenseArcher->setState("idle");
			}
		}
	}
}


void ChessSpawn::update(float dt)
{
	this->setAction();
}
