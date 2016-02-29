#include "GameLayer.h"

#include <algorithm>
#include <random>

#include "Cloud.h"
#include "Constants.h"
#include "Collectable.h"
#include "ScoreLayer.h"
#include "Stage.h"
#include "SoundManager.h"
#include "SpecialCollectable.h"

using namespace cocos2d;

const std::string imageScore = "score.png";
const std::string imagePause = "btn_pause.png";
const std::string imageResume = "btn_resume.png";
const std::string imageFinger_1 = "finger_1.png";
const std::string imageFinger_2 = "finger_2.png";
const std::string imageExplosion = "explosion.png";
const std::string imageProgressBar = "progress.png";
const std::string imageLoadingWheel = "loading.png";
const std::string imageUnlockedItem_pizza = "unlockeditem_pizza.png";
const std::string imageUnlockedItem_staticBomb = "unlockeditem_staticbomb.png";
const std::string imageUnlockedItem_floatingBomb = "unlockeditem_floatingbomb.png";
const std::string imageUnlockedItem_magnetEffect = "unlockeditem_magneteffect.png";
const std::string imageUnlockedItem_invisibility = "unlockeditem_invisibility.png";

const std::string magnetized = "magnetized";

GameLayer* GameLayer::_instance = 0;
static Stage _stage;  // To pass which stage we are playing now.

Scene* GameLayer::createScene(Stage const& stage)
{
    // hold the stage and set it as played and pass that to MainMenuLayer through GameOverLayer
    _stage = stage;

    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    if (not layer) { return nullptr; }

    // Singletone Instance
    _instance = layer;
    scene->addChild(layer);

    // add Score HUD
    {
        ScoreLayer* scoreLayer = ScoreLayer::create();
        scene->addChild(scoreLayer);
        layer->_scoreHUD = scoreLayer;
    }

    // add the Pause HUD Layer
    {
        PauseLayer* pauseLayer = PauseLayer::create();
        scene->addChild(pauseLayer);
        pauseLayer->setVisible(false);
        layer->_pauseHUD = pauseLayer;
    }

    // add GameOver HUD Layer
    {
        GameOverLayer* gameOverLayer = GameOverLayer::create();
        scene->addChild(gameOverLayer);
        gameOverLayer->setVisible(false);
        layer->_gameOverHUD = gameOverLayer;
    }

    // return the scene
    return scene;
}

GameLayer* GameLayer::getInstance() {
    if (not _instance) {
        _instance = GameLayer::create();
    }
    return _instance;
}

Stage GameLayer::getStage() {
    return _stage;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    // 1. Super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) ) {
        return false;
    }

    // 2. Origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
     CCLOG("===== GameLayer _visibleSize width-height (%dx%d)", (int)_visibleSize.width, (int)_visibleSize.height);
    // CCLOG("GameLayer _origin (x, y) (%f, %f)", _origin.x, _origin.y);


    _state = GameState::init;
    Trampoline::isDrawingOngoing = false;   // new trampoline drawing can begin

    _stageLength = _stageRemaining = _visibleSize.width * STAGE_LENGTH;  // _visibleSize.width: 480.000
    _distanceForNewCollectables = _visibleSize.width * 0.5; // moving ahead first collectable spwaning

    // this determines when to make a bomb/life fall.
    _distanceForNewSpecialObject = _visibleSize.width * 1.5;
    
    _score = 0;
    _collectedPizzas = 0;
    _totalEggs = 0;
    _totalPizzas = 0;
    
    // add static background for the infinite stage
    if (_stage.getName() == StageStatus::infinite) {
        addBG();
    }

    // Add background
    addFirstLayer();

    // Add layerTwo. collectable spawns based on this layer.
    addSecondLayer();

    // Ground and layer_two is attached in the infinite stage, so no need to add GroundLayer seperately
    if (_stage.getName() != StageStatus::infinite) {
        addGroundLayer();
    }

    // Add chicken
    addChicken();

    // Pause/Resume toggle
    addPauseMenu();
    
    // LoadingBar
    if (_stage.getName() != StageStatus::infinite) {
        addProgressBar();
    }
    
    // Add tutorial once resource loading is complete
    
    // Show unlocked item
    
    
    // Loading
    addLoadingWheel();
    
    // create pointers
    _collectable = std::make_shared<Collectable>(_stage);
    _specialCollectable = std::make_shared<SpecialCollectable>(_stage);


    // Spawn cloud
    this->schedule(schedule_selector(GameLayer::spawnCloud), CLOUD_SPAWN_FREQUENCY * _visibleSize.width);
    
    this->schedule(schedule_selector(GameLayer::updateInvisibilityStopwatch), 1);
    this->schedule(schedule_selector(GameLayer::updateMagnetStopwatch), 1);
    this->schedule(schedule_selector(GameLayer::elapsedTime), 1);

    // Listen for collision
    addContactListners();
    
    // Listen for touches
    addTouchListners();

    // Activate main update loop
    this->scheduleUpdate();

    return true;
}

void GameLayer::onEnterTransitionDidFinish() {
    // Add background's rest of the images
    if (_layerBackground) {
        _layerBackground->addScrollingImages();
    }
    
    // Add layerTwo's rest of the images
    if (_layerTwo) {
        _layerTwo->addScrollingImages();
    }
    
    // Add layerGround's rest of the images
    if (_stage.getName() != StageStatus::infinite) {
        _layerGround->addScrollingImages();
    }
    
    if (_loading) {
        this->removeChild(_loading);
        
        // add tutorial
        addTutorial();
        
        showUnlockedItem(getStage());
    }
}

void GameLayer::addBG() {
    auto bg = Sprite::create("bg.png");
    if (not bg) { return; }
    
    bg->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(bg, BackgroundLayer::layerBG);
}

void GameLayer::addChicken() {
    _chicken = std::make_shared<Chicken>();
    _chicken->createChicken(this);
    _chicken->setLives(CHICKEN_LIVES);
}

void GameLayer::addContactListners() {
    auto contactListener = EventListenerPhysicsContact::create();
    if (not contactListener) { return; }

    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameLayer::addExplosionEffect() {
    // Explosion Effect
    ParticleExplosion* explosion = ParticleExplosion::createWithTotalParticles(66);
    explosion->setTexture(Director::getInstance()->getTextureCache()->addImage(imageExplosion));
    explosion->setStartColor(Color4F::YELLOW);
    explosion->setEndColor(Color4F::YELLOW);
    explosion->setScale(0.75);
    explosion->setSpeed(5);
    explosion->setPosition(_chicken->getPosition());
    this->addChild(explosion, BackgroundLayer::layerTouch);

    SoundManager::Play(SoundManager::soundExplosion);    // play bomb sound
}

void GameLayer::addFirstLayer() {
    _layerBackground = std::make_shared<LayerBackground>(_stage);
    
    if (not _layerBackground) { return; }
    
    _layerBackground->createLayer(this);
}

void GameLayer::addGroundLayer() {
    _layerGround = std::make_shared<LayerGround>(_stage);

    if (not _layerGround) { return; }
    
    _layerGround->createLayer(this);
}

void GameLayer::addLoadingWheel() {
    _loading = Label::createWithTTF("Loading...", font, _visibleSize.height * SCORE_FONT_SIZE);
    
    if (not _loading) { return; }

    _loading->setColor(Color3B::ORANGE);
    _loading->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.75));
    this->addChild(_loading, BackgroundLayer::layerTouch);
}

void GameLayer::addPauseMenu() {
    MenuItem* pause = MenuItemImage::create(imagePause, imagePause, CC_CALLBACK_1(GameLayer::pauseGame, this));
    _pauseMenu = Menu::create(pause, NULL);
    _pauseMenu->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.95)); // position updated in update fn
    this->addChild(_pauseMenu, BackgroundLayer::layerChicken);

    _pauseMenu->setVisible(false); // get visible when we start to play
}

void GameLayer::addProgressBar() {
    _progressBar = cocos2d::ui::LoadingBar::create();
    _progressBar->loadTexture(imageProgressBar);
    _progressBar->setColor(Color3B::ORANGE);
    _progressBar->setPercent(0);
    
    _progressBar->setPosition(Point(_visibleSize.width * 0.5, _progressBar->getContentSize().height));
    this->addChild(_progressBar, BackgroundLayer::layerTouch);
}

void GameLayer::addSecondLayer() {
    _layerTwo = std::make_shared<LayerTwo>(_stage);
    
    if (not _layerTwo) { return; }
    
    _layerTwo->createLayer(this);
}

void GameLayer::addTouchListners() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameLayer::addTutorial() {
    _finger = Sprite::create(imageFinger_1);
    if (not _finger) { return; }

    _finger->setAnchorPoint(Vec2(0, 0));
    _finger->setPosition(_visibleSize.width * 0.20, _visibleSize.height * 0.20);
    this->addChild(_finger, BackgroundLayer::layerChicken);

    auto click = CallFunc::create( [this](){ _finger->setTexture(imageFinger_2); });
    MoveTo* draw = MoveTo::create(2, Point(_visibleSize.width * 0.5, _finger->getPositionY()));
    auto reset = CallFunc::create( [this](){
        _finger->setPosition(Vec2(_visibleSize.width * 0.20, _finger->getPositionY()));
        _finger->setTexture(imageFinger_1);
    });
    auto delay = DelayTime::create(0.25f);
    auto seq = Sequence::create(delay, click, delay, draw, delay, reset, NULL);
    auto tutorial = RepeatForever::create((ActionInterval*)seq);
    _finger->runAction(tutorial);
}

void GameLayer::cleanTrampoline() {
    this->removeChild(_trampoline->getTrampoline());
    Trampoline* temp = _trampoline;
    _trampoline = nullptr;
    delete temp;
}

void GameLayer::drawNewTrampoline() {
    _trampoline = new Trampoline();
    if (not _trampoline) { return; }

    // trampoline starting point is moving alone with the speedX
    _lineStartPoint.x -= LAYER_TWO_SPEED * _visibleSize.width * _chicken->getVectorX();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
}

void GameLayer::elapsedTime(float tick) {
    _elapsedTime += 1;
}

void GameLayer::endOfStage() {
    _chicken->setVector(Vec2(0, 0));

    if (_chicken->getChicken() and _state == GameState::finishing) {
        auto delay = DelayTime::create(1);

        auto chickenTakePosition = MoveTo::create(1.0, Point(_chicken->getPosition().x, _visibleSize.height * 0.60));
        auto chickenAchieveEnergy = MoveTo::create(1.0, Point(_chicken->getChicken()->getContentSize().width, _visibleSize.height * 0.60));
        auto chickenRunThrough = MoveTo::create(1.0, Point(_visibleSize.width + _chicken->getChicken()->getContentSize().width * 2, _visibleSize.height * 0.60));

        TargetedAction* acChickenMove1 = TargetedAction::create(_chicken->getChicken(), chickenTakePosition);
        TargetedAction* acChickenMove2 = TargetedAction::create(_chicken->getChicken(), chickenAchieveEnergy);
        TargetedAction* acChickenMoveToFinish = TargetedAction::create(_chicken->getChicken(), chickenRunThrough);

        // last two delays are to finish chicken's move b4 going to finished state
        Sequence* finishingActions = Sequence::create(acChickenMove1, delay, delay, delay, acChickenMove2, acChickenMoveToFinish, NULL);
        this->runAction(finishingActions);
        _state = GameState::finished;
    }
}

void GameLayer::focusOnCharacter() {
    if(_chicken->getPosition().y > _visibleSize.height * 0.6f) {
        this->setPositionY( (_visibleSize.height * 0.6f - _chicken->getPosition().y) * 0.8f);
    } else {
        this->setPositionY(0);
    }
}

void GameLayer::gameOver(int stageCompletionPercentage) {
    _state = GameState::terminate; // set gamestate as terminate to stop schedule update
    
    // Game over score and others
    _gameOverHUD->setup(_stage, _score, _totalEggs, _collectedPizzas, _totalPizzas, _elapsedTime, stageCompletionPercentage);
    _gameOverHUD->setVisible(true);
    _pauseMenu->setVisible(false);
}

void GameLayer::handleCollectableConsumption(Sprite* collectable) {
    // 2:egg 4:pizza 8:all_type_of_bombs 16:life 32:invisibility 64:trampoline 128:magnet_effect
    switch (collectable->getTag()) {
        case 2: {     // scrolling egg
            // Egg collection is the basic goal of the game.
            ++_score;
            updateScoreLabel();

            // play collection sound
            SoundManager::Play(SoundManager::soundPickupCoin);

            // remove the object the chicken collided with
            removeCollectable(collectable);
            break;
        }
        case 4: {    // scrolling pizza
            _chicken->increaseSpriteSize();
            ++_collectedPizzas;

            {// delay + decreaseSize + delay + decreaseSize + delay + decreaseSizeToNormal
                auto callback = CallFunc::create([this]() {
                    _chicken->resetSizeAndWeight();
                } );

                auto delay = DelayTime::create(3.0f);

                _chicken->getChicken()->stopAction(_sequence);
                _sequence = Sequence::create(delay,
                                             ScaleTo::create(2.0f, 1.0f),
                                             callback,
                                             NULL);
                _chicken->getChicken()->runAction(_sequence);
            }

            // play food sound
            SoundManager::Play(SoundManager::soundPickupFood);

            // remove the object the chicken collided with
            removeCollectable(collectable);
            break;
        }
        case 8: {    // all_type_of_bombs
            if (_chicken->isInvisible()) { break; }
            if (_chicken->getState() == PlayerState::newBorn) { break; } // shouldn't hit two bombs in microseconds
            
            _chicken->getChicken()->setVisible(false);

            addExplosionEffect();

            _chicken->decreaseLife();
            _scoreHUD->updateLife(_chicken->getLives());

            if (not _chicken->getLives()) {
                lastLifeExploded();
            }
            else {
                // have more lives
                _chicken->setState(PlayerState::newBorn);
            }

            // remove the object the chicken collided with
            removeCollectable(collectable);
            removeSpecialCollectable(collectable);
            break;
        }
        case 16: {    // bonus life
            _chicken->increaseLife();
            _scoreHUD->updateLife(_chicken->getLives());
            removeSpecialCollectable(collectable);
            
            SoundManager::Play(SoundManager::soundLifeup);
            break;
        }
        case 32: {    // invisibility
            removeSpecialCollectable(collectable);
            _chicken->makeInvisible();
            SoundManager::Play(SoundManager::soundLifeup);
            _scoreHUD->startStopwatch(2);
            
            this->stopActionByTag(2); // reset
            auto makeVisible = CallFunc::create([this](){ _chicken->makeVisible(); });
            auto seq = Sequence::create(DelayTime::create(EFFECT_DURATION + 1), makeVisible, NULL);
            seq->setTag(2); // invisibility tag: 2
            this->runAction(seq);
            
            break;
        }
        case 64: {    // Trampoline, so no action here.
            break;
        }
        case 128: {   // magnet effect
            removeSpecialCollectable(collectable);
            _chicken->setMagnetEffect(true);
            SoundManager::Play(SoundManager::soundLifeup);
            _scoreHUD->startStopwatch(1);
            
            this->stopActionByTag(1); // reset
            auto disableEffect = CallFunc::create([this](){ _chicken->setMagnetEffect(false); });
            auto seq = Sequence::create(DelayTime::create(EFFECT_DURATION + 1), disableEffect, NULL);
            seq->setTag(1); // magnet_effect tag: 1
            this->runAction(seq);
            
            break;
        }
        default:
            CCLOG("GameLayer::handleCollectableConsumption():: Unknown collectable tag");
            break;
    }
}

// Set scoreHUD lives with Chicken's lives
void GameLayer::initScoreHUDLives() {
    _scoreHUD->initLifeSprites(_chicken->getLives());
}

void GameLayer::jump(float trampolinePositionY) {
    if (_chicken->getPosition().y > trampolinePositionY and
        _chicken->getState() == PlayerState::falling) {

        _chicken->setState(PlayerState::jumping);
        SoundManager::Play(SoundManager::soundJump);
        speedUp();
        // releaseTouch(); // finish trampoline drawing
    }
}

void GameLayer::lastLifeExploded() {
    // chicken dead. game over.
    auto callbackStopMovement = CallFunc::create([this](){
        _chicken->setState(PlayerState::start);
    });
    auto callbackChickenDead = CallFunc::create([this](){
        _chicken->setState(PlayerState::dying);
    });

    Sequence* action = Sequence::create(callbackStopMovement, DelayTime::create(3.0), callbackChickenDead, NULL);
    this->runAction(action);
}

void GameLayer::pauseGame(cocos2d::Ref const* sender) {
    if (_state != GameState::started) { return; }

    Director::getInstance()->pause();
    _state = GameState::paused;

    _pauseHUD->setVisible(true);
    _pauseMenu->setVisible(false);
}

void GameLayer::resumeClicked(cocos2d::Ref const* sender) {
    // don't change the GameState.
    // set resume in Director and show a FadeOut action of "Ready..?" label
    // then a callback to set GameState and others.

    if (_state != GameState::paused) { return; }

    _pauseHUD->setVisible(false);
    Director::getInstance()->resume();

    auto resumeLabel = Label::createWithTTF("3", font, _visibleSize.height * GO_FONT_SIZE);

    auto resume = CallFunc::create([resumeLabel, this]() {
        this->resumeGame(this);
        resumeLabel->setString("");
    });

    auto two = CallFunc::create([resumeLabel]() {
        resumeLabel->setString("2");
    });

    auto one = CallFunc::create([resumeLabel]() {
        resumeLabel->setString("1");
    });
    
    auto delay = DelayTime::create(1.0f);

    if (resumeLabel) {
        resumeLabel->setColor(Color3B::YELLOW);
        resumeLabel->setAnchorPoint(Vec2(0, 0));
        resumeLabel->setPosition(_visibleSize.width * 0.5 - resumeLabel->getContentSize().width * 0.5,
                                 _visibleSize.height * 0.75 - resumeLabel->getContentSize().height * 0.5);
        this->addChild(resumeLabel, BackgroundLayer::layerChicken);

        resumeLabel->runAction(Sequence::create(delay,
                                                two,
                                                delay,
                                                one,
                                                delay,
                                                resume,
                                                NULL));
    }

}

void GameLayer::resumeGame(cocos2d::Ref const* sender) {
    if (_state != GameState::paused) { return; }

    _state = GameState::started;
    _pauseMenu->setVisible(true);
}

void GameLayer::removeCollectable(cocos2d::Sprite* collectable) {
    // cleanup
    this->removeChild(collectable);

    if (std::find(_collectables.begin(), _collectables.end(), collectable) != _collectables.end()) {
        // remove the item from _collectables list
        _collectables.erase(std::find(_collectables.begin(), _collectables.end(), collectable));
    }
}

void GameLayer::removeSpecialCollectable(cocos2d::Sprite* collectable) {
    // cleanup
    this->removeChild(collectable);

    if (std::find(_specialCollectables.begin(), _specialCollectables.end(), collectable) != _specialCollectables.end()) {
        // remove the item from _collectables list
        _specialCollectables.erase(std::find(_specialCollectables.begin(), _specialCollectables.end(), collectable));
    }
}

void GameLayer::releaseTouch() {
    if (_trampoline) { Trampoline::isDrawingOngoing = false; }
    _lineStartPoint = _lineEndPoint;
}

void GameLayer::showUnlockedItem(Stage const& stage) {
    if (stage.isPlayed()) return;
    
    if (stage.getName() == StageStatus::england) {
        _unlockedItem = nullptr;
    }
    if (stage.getName() == StageStatus::italy) {
        _unlockedItem = Sprite::create(imageUnlockedItem_pizza);
    }
    if (stage.getName() == StageStatus::france) {
        _unlockedItem = Sprite::create(imageUnlockedItem_staticBomb);
    }
    if (stage.getName() == StageStatus::germany) {
        _unlockedItem = Sprite::create(imageUnlockedItem_floatingBomb);
    }
    if (stage.getName() == StageStatus::spain) {
        _unlockedItem = Sprite::create(imageUnlockedItem_magnetEffect);
    }
    if (stage.getName() == StageStatus::netherlands) {
        _unlockedItem = Sprite::create(imageUnlockedItem_invisibility);
    }
    if (stage.getName() == StageStatus::infinite) {
        _unlockedItem = nullptr;
    }

    if (not _unlockedItem) { return; }
    
    _unlockedItem->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.6);
    this->addChild(_unlockedItem, BackgroundLayer::layerChicken);
}

void GameLayer::spawnCollectable() {
    if (_state != GameState::started) { return; }

    if (not _collectable) { return; }
    Spawned spawned = _collectable->spawn(this, _collectables);

    // count number of eggs, and pizzas
    if (spawned.first == 2) {
        _totalEggs += spawned.second;
    }
    if (spawned.first == 4) {
        _totalPizzas += spawned.second;
    }
}

void GameLayer::spawnSpecialObject() {
    if (_state != GameState::started) { return; }

    if (not _specialCollectable) { return; }
    _specialCollectable->spawn(this, _specialCollectables);
}

void GameLayer::spawnCloud(float dt) {
    if (_state != GameState::started) { return; }

    Cloud* cloud = new Cloud();
    cloud->spawn(this);
}

void GameLayer::speedUp() {
    float xDist = (_lineEndPoint.x - _lineStartPoint.x);
    float yDist = (_lineEndPoint.y - _lineStartPoint.y);

    if (_lineStartPoint.x > _lineEndPoint.x) {
        xDist = (_lineStartPoint.x - _lineEndPoint.x);
        yDist = (_lineStartPoint.y - _lineEndPoint.y);
    }

    float degree = atan2(yDist, xDist) * 180 / PI;

    _chicken->applySpeedX(-degree * CUSTOM_ACCELERATION);
}


// ########## TOUCH EVENTS ########## //
#pragma mark Touch Events
bool GameLayer::onTouchBegan(Touch const* touch, Event const* event) {

    if (_state == GameState::finished or
        _state == GameState::paused or
        _state == GameState::terminate or
        Trampoline::isDrawingOngoing) {
    
        return false;
    }

    // disable the tutorial
    if (_state == GameState::init) {
        _state = GameState::started;
        
        if (_finger) {
            _finger->stopAllActions();
            this->removeChild(_finger);
        }
        
        // remove unlocked item
        if (_unlockedItem) {
            this->removeChild(_unlockedItem);
        }

        _pauseMenu->setVisible(true);
        
        _elapsedTime = 0; // start game timer
    }

    // start preparation to draw new trampoline
    _lineStartPoint = touch->getLocation();
    _lineEndPoint = _lineStartPoint;
    Trampoline::isDrawingOngoing = true; // start trampoline drawing

    // Remove old trampoline
    if (_trampoline) {
        cleanTrampoline();
    }

    return true;
}

void GameLayer::onTouchMoved(Touch const* touch, Event const* event) {
    // continue only if trampoline drawing is ongoing
    if (_state == GameState::finished or _state == GameState::paused or not Trampoline::isDrawingOngoing) { return; }

    if (touch->getLocation() == _lineStartPoint) { return; }
    if (touch->getLocation().distance(_lineStartPoint) < 30) { return; } // 30 is just trampoline sprite's twice width

    // Remove old trampoline
    if (_trampoline) {
        cleanTrampoline();
    }

    // don't draw trampoline above the screen height
    if (_lineStartPoint.y - this->getPositionY() > _visibleSize.height) { return; }

    // Draw new trampoline
    _trampoline = new Trampoline();
    if (not _trampoline) { return; }

    _lineEndPoint = touch->getLocation();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
    // trampoline drawing is finished once we reach the max length of trampoline
}

void GameLayer::onTouchEnded(Touch const* touch, Event const* event) {
    Trampoline::isDrawingOngoing = false;
}


// ########## COLLISION HANDLING ########## //
#pragma mark Collision Detection
bool GameLayer::onContactBegin(cocos2d::PhysicsContact const& contact) {
    // CCLOG("CONTACT");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    // collision between chicken and trampoline
    if ((a->getCategoryBitmask() == CATEGORY_BITMASK_CHICKEN and b->getCategoryBitmask() == CATEGORY_BITMASK_TRAMPOLINE)) {
        auto trampoline = (Sprite*)contact.getShapeB()->getBody()->getNode();
        jump(trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY());
    }
    // collision between trampoline and chicken
    else if ((a->getCategoryBitmask() == CATEGORY_BITMASK_TRAMPOLINE and b->getCategoryBitmask() == CATEGORY_BITMASK_CHICKEN)) {
        auto trampoline = (Sprite*)contact.getShapeA()->getBody()->getNode();
        jump(trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY());
    }


    // collision between chicken and collectables
    if (a->getCategoryBitmask() == CATEGORY_BITMASK_CHICKEN and (b->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_EGG or
                                                                 b->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_PIZZA or
                                                                 b->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_BOMB or
                                                                 b->getCategoryBitmask() == CATEGORY_BITMASK_INVISIBILITY or
                                                                 b->getCategoryBitmask() == CATEGORY_BITMASK_MAGNET or
                                                                 b->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_LIFE))
    {
        auto collectable = (Sprite*)contact.getShapeB()->getBody()->getNode();
        if (collectable) {
            handleCollectableConsumption(collectable);
        }
    }
    // collision between collectables and chicken
    else if (b->getCategoryBitmask() == CATEGORY_BITMASK_CHICKEN and (a->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_EGG or
                                                                      a->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_PIZZA or
                                                                      a->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_BOMB or
                                                                      a->getCategoryBitmask() == CATEGORY_BITMASK_INVISIBILITY or
                                                                      a->getCategoryBitmask() == CATEGORY_BITMASK_MAGNET or
                                                                      a->getCategoryBitmask() == CATEGORY_BITMASK_COLLECT_LIFE))
    {
        auto collectable = (Sprite*)contact.getShapeA()->getBody()->getNode();
        if (collectable) {
            handleCollectableConsumption(collectable);
        }
    }

    return true;
}

// ########## UPDATE ########## //
#pragma mark Update
void GameLayer::update(float dt) {
    if (_state == GameState::init or _state == GameState::paused or _state == GameState::terminate) { return; }
    if (not _chicken) { return; }

    // TODO: refactor following two ifs. both calls gameOver() with same param
    if (_state == GameState::finished and _chicken->getPosition().x >= _visibleSize.width) {
        // goto game over scene with state: stage cleared
        gameOver(_progressBar->getPercent());
    }

    if (_chicken->getState() == PlayerState::dying) {
        // goto game over scene with state: stage not cleared
        gameOver(_progressBar->getPercent());
    }
    else {
        // chicken is alive and game state is ongoing
        if (_layerBackground) { _layerBackground->update(LAYER_BACKGROUND_SPEED * _visibleSize.width * _chicken->getVectorX()); }
        if (_layerTwo) {
            float layerTwoSpeed = LAYER_TWO_SPEED * _visibleSize.width * _chicken->getVectorX();
            _layerTwo->update(layerTwoSpeed);

            updateStageComplesion(layerTwoSpeed);
        }
        if (_stage.getName() != StageStatus::infinite and _layerGround) {
            _layerGround->update(LAYER_GROUND_SPEED * _visibleSize.width * _chicken->getVectorX());
        }

        if (_trampoline) { _trampoline->update(_chicken->getVectorX()); }
        if (_chicken) { _chicken->update(dt); }

        // if user tap to start to draw trampoline, and then doesn't move finger: keep drawing
        if (_trampoline and Trampoline::isDrawingOngoing) {
            cleanTrampoline();

            drawNewTrampoline();
            // Trampoline drawing is finished once we reach the max length of trampoline.
        }

        updateCollectables(_chicken->getVectorX());
        updateSpecialCollectables(_chicken->getVectorX());

        // keep the camera on the player
//        focusOnCharacter();

        // stage about to finish
        if (_state == GameState::finishing and not _collectables.size()) {
            _pauseMenu->setVisible(false);

            _chicken->setState(PlayerState::start);

            // remove the last trampoline alive
            if (_trampoline) {
                cleanTrampoline();
            }

            // slow down in 2% decrease reate
            _chicken->applySpeedX(-_chicken->getVectorX() * 0.02);

            {
                // don't collide with anything anymore
                _chicken->setCollideToNone();
            }

            if (_chicken->getVectorX() <= 1) {
                endOfStage();
            }
        }
    }
}

void GameLayer::updateSpecialCollectables(float playerSpeed) {
    for (auto i = _specialCollectables.begin(); i != _specialCollectables.end(); ++i) {

        if (not *i) { continue; }

        Vec2 currentPosition = (*i)->getPosition();
        (*i)->setPosition(Vec2(currentPosition.x - COLLECTABLE_SPEED * _visibleSize.width * playerSpeed * 0.30,
                               currentPosition.y - COLLECTABLE_FALLING_SPEED * _visibleSize.height));

        if (currentPosition.y < -(*i)->getContentSize().height) {
            this->removeChild(*i);
            _specialCollectables.erase(i);
            --i; // handle new number one's position in next iteration
        }
    }
}

void GameLayer::updateCollectables(float playerSpeed) {
    for (int i = 0; i < _collectables.size(); ++i) {
        Sprite* s = _collectables.at(i);
        if (not s) { continue; }

        // Scroll
        if (s->getName() != magnetized) {
            s->setPositionX(s->getPosition().x - COLLECTABLE_SPEED * _visibleSize.width * playerSpeed);
        }
        
        // Calculation for Magnet Effect
        Vec2 endPoint = _chicken->getPosition();
        float distance = endPoint.getDistance(s->getPosition());
        
        if ((_chicken->hasMagnetEffect() and
             s->getTag() == CATEGORY_BITMASK_COLLECT_EGG /* Eggs only */
             and distance < _visibleSize.width * 0.3) or
             s->getName() == magnetized) {
            
            // set unique name to be excluded from scrolling
            s->setName(magnetized);
            
            if (not s->getActionByTag(1)) {
                auto magnetEffect = MoveTo::create(1.0, endPoint);
                magnetEffect->setTag(1);
                
                auto stop = [=](){ s->stopActionByTag(1); };
                
                auto seq = Sequence::create(magnetEffect, stop, NULL);

                s->runAction(seq);
            }
            
            //  continue; // this Sprite will be captured by the magnet. no need to check if its out of the screen anymore.
            //  aaa what the hell... let it be captured by the boundary. once the sprite is over the left boundary...its erased
            
        } // Magnet Effect work ends

        if (s->getPositionX() < -s->getContentSize().width) {
            this->removeChild(s);
            _collectables.erase(_collectables.begin() + i);

            --i; // handle new number one's position in next iteration
        }
    }
}

void GameLayer::updateScoreLabel() {
    if (_scoreHUD) {
        _scoreHUD->updateScore(_score);
    }
}

void GameLayer::updateStageComplesion(float speed) {
    _distanceForNewCollectables += speed;
    _distanceForNewSpecialObject += speed;

    if (_distanceForNewCollectables > _visibleSize.width * 0.5) {
        if (_stage.getName() != StageStatus::infinite) {
            _stageRemaining -= _distanceForNewCollectables;
            CCLOG("Stage Remaining: %f", _stageRemaining);
            
            // update progress bar
            if (_progressBar) {
                _progressBar->setPercent(((_stageLength - _stageRemaining - (_visibleSize.width * 0.5)) / _stageLength) * 100);
            }
        }

        _distanceForNewCollectables = 0;

        // spawn collectables based on scrolled length
        spawnCollectable();

        // FINISH THE STAGE
        if (_stageRemaining <= 0) {
            _state = GameState::finishing;
        }
    }

    if (_distanceForNewSpecialObject > _visibleSize.width * SPECIAL_OBJ_SPAWN_DISTANCE) {
        _distanceForNewSpecialObject = 0;

        spawnSpecialObject();
    }
}

void GameLayer::updateInvisibilityStopwatch(float dt) {
    if (not _chicken->isInvisible()) { return; }
    _scoreHUD->tick(2);
}

void GameLayer::updateMagnetStopwatch(float dt) {
    if (not _chicken->hasMagnetEffect()) { return; }
    _scoreHUD->tick(1);
}
