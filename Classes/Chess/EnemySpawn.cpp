#include "EnemySpawn.h"
#include "Scenes/GameScene.h"
#include "DefineBitmask.h"
#include "Scenes/GameScene.h"
#include "Audio/AudioManager.h"
EnemySpawn* EnemySpawn::create(GameScene* scene)
{
	auto newObject = new EnemySpawn();
	if (newObject != nullptr && newObject->init(scene)) {

		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}
bool EnemySpawn::init(GameScene* scene) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_scene = scene;
	soldierCount = 0;
	archerCount = 0;
	isFirstWave = true;
	enemyBase = Base::create();
	addPhysics(enemyBase);
	enemyBase->setFlippedX(-1);
	enemyBase->setAnchorPoint(Vec2(1, 0));
	enemyBase->setPosition(Vec2(visibleSize.width * 0.99, visibleSize.height * 0.34));
	enemyBase->setScale(visibleSize.height / enemyBase->getContentSize().height * 0.2);
	_scene->addChild(enemyBase, 10);
	enemies.pushBack(enemyBase);

	spawnDefenseArcher("Archer"+getLevelString());

	auto baseBar = ui::LoadingBar::create("Red_Bar.png");
	baseBar->setScale(visibleSize.height / baseBar->getContentSize().height * 0.07);
	baseBar->setPosition(Vec2(visibleSize.width * 0.60, visibleSize.height * 0.75));
	baseBar->setAnchorPoint(Vec2(0, 0.5));
	_scene->addChild(baseBar, 5);
	baseBar->setDirection(ui::LoadingBar::Direction::LEFT);
	baseBar->setPercent(100);
	baseBar->schedule([=](float delta) {
		baseBar->setPercent((float)enemyBase->getHealth() / enemyBase->getHealthController()->getMaxHealth() * 100);
		}, "updateBaseBar");
	auto baseBarBG = Sprite::create("Red_Bar_Bg.png");
	baseBarBG->setPosition(baseBar->getPosition());
	baseBarBG->setScale(visibleSize.height / baseBar->getContentSize().height * 0.07);
	baseBarBG->setAnchorPoint(Vec2(0, 0.5));
	_scene->addChild(baseBarBG, 4);

	auto Cs01 = Sprite::create("Cs02.png");
	Cs01->setPosition(baseBar->getPosition());
	Cs01->setScale(0.8);
	_scene->addChild(Cs01, 6);

	auto COMPUTER = Label::createWithTTF("COMPUTER", "fonts/KnightWarrior.otf", 36);
	//goldLabel->setColor(Color3B::YELLOW);
	COMPUTER->setPosition(Vec2(visibleSize.width * 0.70, visibleSize.height * 0.82));
	_scene->addChild(COMPUTER, 7);

	this->scheduleUpdate();
	return true;
}

void EnemySpawn::startSpawn() {
	int spawnInterval = 5;
	soldierCount = 0;
	archerCount = 0;
	assassinCount = 0;
	combatantCount = 0;
	spawnTimer = 0;
	_scene->schedule([=](float dt) {
		if (spawnTimer <= 50) {
			if (spawnTimer % (spawnInterval * 2) < spawnInterval) {
				if (soldierCount < 2) {
					spawnEnemy("Soldier"+getLevelString());
					archerCount = 0;
					soldierCount++;
				}
				else if (archerCount < 1) {
					spawnEnemy("Archer" + getLevelString());
					soldierCount = 0;
					archerCount++;
				}
			}
		}
		else {
			if (spawnTimer % (spawnInterval * 2) < spawnInterval) {
				if (soldierCount < 2) {
					spawnEnemy("Soldier" + getLevelString());
					archerCount = 0;
					soldierCount++;
				}
				else if (archerCount < 1) {
					spawnEnemy("Archer" + getLevelString());
					assassinCount = 0;
					archerCount++;
				}
				else if (assassinCount < 1) {
					spawnEnemy("Assassin" + getLevelString());
					combatantCount = 0;
					assassinCount++;
				}
				else if (combatantCount < 1) {
					spawnEnemy("Combatant" + getLevelString());
					soldierCount = 0;
					combatantCount++;
				}
			}
			if (spawnTimer>120)
			{
				if (getLevel()<5)
				{
					LevelUp();
				}
				spawnTimer = 0;
			}
		}

		spawnTimer += 5;
		}, 2.0f, "spawnEnemy");
}

void EnemySpawn::spawnEnemy(std::string tyleChess)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Chess* chess = Chess::createChess(tyleChess);
	addPhysics(chess);
	chess->setState("walk");
	chess->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.45));
	_scene->addChild(chess);

	enemies.pushBack(chess);
}

void EnemySpawn::addPhysics(Chess* chess)
{
	PhysicsBody* physics;
	if (dynamic_cast<Soldier5*>(chess)!=nullptr || dynamic_cast<Combatant5*>(chess))
	{
		Vec2 points[] = { Vec2(15, -50), Vec2(100, -50), Vec2(100, 50), Vec2(15, 50) };
		physics = PhysicsBody::createPolygon(points, 4);
	}
	else
	{
		physics= PhysicsBody::createBox(chess->getContentSize() * 0.6);
	}
	physics->setDynamic(false);
	physics->setCategoryBitmask(DefineBitmask::Enemy);
	physics->setContactTestBitmask(DefineBitmask::Character);
	physics->setCollisionBitmask(DefineBitmask::Character);
	chess->addComponent(physics);
}

void EnemySpawn::spawnDefenseArcher(std::string tyleChess)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (DefenseArcher!=nullptr)
	{
		DefenseArcher->removeFromParentAndCleanup(true);
	}
	DefenseArcher = Chess::createChess(tyleChess);
	DefenseArcher->addAnimationIdle(tyleChess);
	DefenseArcher->setDame(_scene->getLevel() * 5 + DefenseArcher->getDame()-5);
	DefenseArcher->setPosition(Vec2(visibleSize.width * 0.94, visibleSize.height * 0.43));
	DefenseArcher->setState("idle");
	//DefenseArcher->getHealthController()->setVisible(false);
	_scene->addChild(DefenseArcher,11);
}

void EnemySpawn::LevelUp()
{
	setLevel(getLevel() + 1);
	spawnDefenseArcher("Archer" + getLevelString());
	enemyBase->setLevel(getLevel());
	_scene->setBackGround(getLevelString());
}

void EnemySpawn::setSprites(cocos2d::Vector<Chess*>*sprites)
{
	_sprites = sprites;
}

void EnemySpawn::setAction() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	AudioManager* audioManager = AudioManager::getInstance();
	bool firstElement = true;
	for (auto& chess : enemies) {
		if (firstElement) {
			firstElement = false;
			continue;
		}
		if (chess->getState() == "walk") {
			if (chess->getCurrentState() != "walk") {
				chess->stopAllActions();
				chess->runActionWalk();
				Vec2 chessPosition = chess->getPosition();
				Vec2 basePosition = Vec2(visibleSize.width * 0.1, visibleSize.height * 0.45);
				float distance = chessPosition.distance(basePosition);
				if (distance!=0)
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
					if (sprite->getState()!="die" && sprite->getPosition().getDistance(chess->getPosition()) < visibleSize.width / 4)
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
				if (chess->getCollidingBase()==true)
				{
					chess->setCollidingBase(false);
					bool hasAttackBase = false;
					for (auto& _chess : enemies) {
						if (_chess->getState()!= "die" && _chess->getCollidingBase()==true)
						{
							for (auto& base : *_sprites) {
								base->setColliding(true);
								hasAttackBase = true;
								break;
							}
							break;
						}
					}
					if (hasAttackBase == false)
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
				_scene->setExp(_scene->getExp() + chess->getPrice());
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
	if (DefenseArcher->getState()=="idle")
	{
		if (DefenseArcher->getCurrentState()!="idle")
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
	else if(DefenseArcher->getState() == "attack")
	{
		auto hasColliding = false;
		if (DefenseArcher->getCurrentState()!="attack")
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


void EnemySpawn::update(float dt)
{
	this->setAction();
}


