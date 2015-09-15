#include "GameLayer.h"

#include "Cloud.h"
#include "Constants.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "Egg.h"

using namespace cocos2d;

static const std::string imageScore = "score.png";
static const std::string imagePause = "pause.png";
static const std::string imageResume = "resume.png";
static const std::string imageFinger = "finger.png";
static const std::string soundJump = "jump.wav";
static const std::string soundCollectEgg = "pickup_coin.wav";
static const std::string fontMarkerFelt = "Marker Felt.ttf";

static const int spawnPattern[] = {1, 2, 3, 0, 1, 2, 0, 3, 1, 0, 1, 2, 0, 1, 1, 0, 3, 1, 3, 0};
static const std::vector<int> eggSpawnPattern(spawnPattern, spawnPattern + sizeof(spawnPattern) / sizeof(int));
static int currentPatternIndex = 0;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    // 1. Super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255))) {
        return false;
    }
    
    // 2. Origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("GameLayer _visibleSize width-height (%dx%d)", (int)_visibleSize.width, (int)_visibleSize.height);
    CCLOG("GameLayer _origin (x, y) (%f, %f)", _origin.x, _origin.y);

    _state = GameState::init;
    
    _stageLength = _visibleSize.width * 5;  // _visibleSize.width: 480.000
//    _elapsedStage = 0;
    _elapsedStage = _visibleSize.width * 0.50; // moving ahead egg spwaning
    
    // add static background
//    addBG();

    // Add background
    addFirstLayer();
    
    // Add layerTwo
    addSecondLayer();
    
    // Add layerGround
    addGroundLayer();
    
    // Add chicken
    addChicken();
    
    // Score Label
    addScoreLabel();
    
    // Pause/Resume toggle
    addPauseMenu();
    
    // Tutorial
    addTutorial();
    

    // Spawn cloud
    this->schedule(schedule_selector(GameLayer::spawnCloud), CLOUD_SPAWN_FREQUENCY * _visibleSize.width);
    
    // Spawn egg
//    this->schedule(schedule_selector(GameLayer::spawnEgg), EGG_SPAWN_FREQUENCY * _visibleSize.width);
    

    // Listen for touches
    addTouchListners();
    
    // Listen for collision
    addContactListners();
    

    // Activate main update loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::addBG() {
    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_visibleSize.width * 0.5f, _visibleSize.height * 0.5f));
    this->addChild(bg, BackgroundLayer::layerBG);
}

void GameLayer::addChicken() {
    _chicken = new Chicken();
    _chicken->createChicken(this);
}

void GameLayer::addContactListners() {
    auto contactListener = EventListenerPhysicsContact::create();
    if (not contactListener) { return; }
    
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameLayer::addFirstLayer() {
    _background = new Background();
    _background->createBackground(this);
}

void GameLayer::addGroundLayer() {
    _layerGround = new LayerGround();
    _layerGround->createLayerGround(this);
}

void GameLayer::addPauseMenu()     {
    MenuItem* pause = MenuItemImage::create(imagePause, imagePause, CC_CALLBACK_1(GameLayer::pause, this));
    _pauseMenu = Menu::create(pause, NULL);
    _pauseMenu->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height * 0.95)); // position also updated in update function
    this->addChild(_pauseMenu, BackgroundLayer::layerChicken);
    
    _pauseMenu->setEnabled(false); // enable it when _isGameStarted = true
}

void GameLayer::addSecondLayer() {
    _layerTow = new LayerTwo();
    _layerTow->createLayerTwo(this);
}

void GameLayer::addScoreLabel() {
    _score = 0;
    _scoreIcon = Sprite::create(imageScore);
    _scoreIcon->setAnchorPoint(Vec2(0, 0));
    _scoreIcon->setPosition(_scoreIcon->getContentSize().width, _visibleSize.height * 0.9);
    this->addChild(_scoreIcon, BackgroundLayer::layerChicken);
    
    std::string scoreStr = String::createWithFormat("%d", _score)->getCString();
    _scoreLabel = Label::createWithTTF(scoreStr, fontMarkerFelt, _visibleSize.height * SCORE_FONT_SIZE);
    if (_scoreLabel) {
        _scoreLabel->setColor(Color3B::WHITE);
        _scoreLabel->setAnchorPoint(Vec2(0, 0));
        _scoreLabel->setPosition(_scoreIcon->getContentSize().width * 2.5, _visibleSize.height * 0.89);
        this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
    }
}

void GameLayer::addTouchListners() {
    auto touchListener = EventListenerTouchOneByOne::create();
    if (not touchListener) { return; }
    
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameLayer::addTutorial() {
    _finger = Sprite::create(imageFinger);
    if (not _finger) { return; }
    
    _finger->setAnchorPoint(Vec2(0, 0));
    _finger->setPosition(_visibleSize.width * 0.20, _visibleSize.height * 0.20);
    this->addChild(_finger, BackgroundLayer::layerChicken);
    
    MoveTo* draw = MoveTo::create(2, Point(_visibleSize.width * 0.5, _finger->getPositionY()));
    MoveTo* reset = MoveTo::create(0, Point(_visibleSize.width * 0.20, _finger->getPositionY()));
    auto delay = DelayTime::create(0.25f);
    auto seq = Sequence::create(draw, delay, reset, delay, NULL);
    auto tutorial = RepeatForever::create((ActionInterval*)seq);
    _finger->runAction(tutorial);
}

void GameLayer::drawNewTrampoline() {
    _trampoline = new Trampoline();
    if (not _trampoline) { return; }
    
    _lineStartPoint.x -= LAYER_TWO_SPEED * _visibleSize.width * _chicken->getVectorX();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
}

void GameLayer::endOfStage() {
    _chicken->setVector(Vec2(0, 0));
    spawnEndOfStageItem();

    if (_chicken->getChicken() and _flag and _state == GameState::finishing) {
        auto delay = DelayTime::create(1);
        
        auto chickenAction1 = MoveTo::create(1, Point(_chicken->getPosition().x, _visibleSize.height * 0.60));
        auto flagAction = MoveTo::create(1, Point(_visibleSize.width - _flag->getContentSize().width, _visibleSize.height * 0.5));
        auto chickenAction2 = MoveTo::create(1, Point(_visibleSize.width + _chicken->getChicken()->getContentSize().width, _visibleSize.height * 0.60));
    
        TargetedAction* acChickenMove = TargetedAction::create(_chicken->getChicken(), chickenAction1);
        TargetedAction* acFlagMove = TargetedAction::create(_flag, flagAction);
        TargetedAction* acChickenMoveToFinish = TargetedAction::create(_chicken->getChicken(), chickenAction2);
        
        // last two delays are to finish chicken's move b4 going to finished state
        Sequence* finishingActions = Sequence::create(acChickenMove, delay, acFlagMove, delay, delay, acChickenMoveToFinish, NULL);
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

void GameLayer::jump(float trampolinePositionY) {
    if (_chicken->getPosition().y > trampolinePositionY and
        _chicken->getState() == PlayerState::falling) {
        
        _chicken->setState(PlayerState::jumping);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundJump.c_str());
        speedUp();
        releaseTouch();
    }
}

void GameLayer::pause(cocos2d::Ref* sender) {
    Director::getInstance()->pushScene(PauseLayer::createScene());
}

void GameLayer::removeEggSprite(cocos2d::Sprite *egg) {
    this->removeChild(egg);
    if (std::find(_eggs.begin(), _eggs.end(), egg) != _eggs.end()) {
        _eggs.erase(std::find(_eggs.begin(), _eggs.end(), egg));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundCollectEgg.c_str());
    }
}

void GameLayer::releaseTouch() {
    if (_trampoline) { _trampoline->setDrawingFinished(true); }
    _lineStartPoint = _lineEndPoint;
}

void GameLayer::spawnEgg() {
    if (_state == GameState::started) {
        Egg* egg = new Egg();
        egg->spawn(this, _eggs, eggSpawnPattern.at(currentPatternIndex++ % eggSpawnPattern.size()));
    }
}

void GameLayer::spawnEndOfStageItem() {
    _flag = Sprite::create("flag.png");
    if (not _flag) { return; }
    
    _flag->setPosition(_visibleSize.width + _flag->getContentSize().width * 1.5, _visibleSize.height * 0.5);
    this->addChild(_flag, BackgroundLayer::layerFour);
}

void GameLayer::spawnCloud(float dt) {
    if (_state == GameState::started) {
        Cloud* cloud = new Cloud();
        cloud->spawn(this);
    }
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
bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
    // disable the tutorial
    if (_state == GameState::init) {
        _state = GameState::started;
        _finger->stopAllActions();
        this->removeChild(_finger);
        
        _pauseMenu->setEnabled(true);
    }

    if (_state == GameState::started) {
        _lineStartPoint = touch->getLocation();
        _lineEndPoint = _lineStartPoint;

        // Remove old trampoline
        if (_trampoline) {
            this->removeChild(_trampoline->getTrampoline());
            _trampoline = nullptr;
        }
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event) {

    if (_state == GameState::started) {
        if (touch->getLocation() == _lineStartPoint) { return; }
        if (touch->getLocation().distance(_lineStartPoint) < 30) { return; } // 30 is just trampoline sprite's twice width
        
        // Remove old trampoline
        if (_trampoline) {
            this->removeChild(_trampoline->getTrampoline());
            _trampoline = nullptr;
        }
        
        // don't draw trampoline above the screen height
        if (_lineStartPoint.y - this->getPositionY() > _visibleSize.height) { return; }
        
        // Draw new trampoline
        _trampoline = new Trampoline();
        if (not _trampoline) { return; }

        _lineEndPoint = touch->getLocation();
//        _lineStartPoint.x -= LAYER_TWO_SPEED * _visibleSize.width * _chicken->getVectorX();
        _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
    }
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    if (_trampoline) { _trampoline->setDrawingFinished(true); }
}


// ########## COLLISION HANDLING ########## //
bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {
    // CCLOG("CONTACT");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    // collision between chicken and trampoline
    if ((a->getCategoryBitmask() == 1 and b->getCategoryBitmask() == 2)) {
        auto trampoline = (Sprite*)contact.getShapeB()->getBody()->getNode();
        jump(trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY());
    }
    // collision between trampoline and chicken
    else if ((a->getCategoryBitmask() == 2 and b->getCategoryBitmask() == 1)) {
        auto trampoline = (Sprite*)contact.getShapeA()->getBody()->getNode();
        jump(trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY());
    }
    
    
    // collision between chicken and eggs
    if (a->getCategoryBitmask() == 1 and b->getCategoryBitmask() == 4) {
        _score ++;
        updateScoreLabel();

        // Remove colided egg
        auto egg = (Sprite*)contact.getShapeB()->getBody()->getNode();
        if (egg) { removeEggSprite(egg); }
    }
    // collision between eggs and chicken
    else if (a->getCategoryBitmask() == 4 and b->getCategoryBitmask() == 1) {
        _score ++;
        updateScoreLabel();

        // Remove colided egg
        auto egg = (Sprite*)contact.getShapeA()->getBody()->getNode();
        if (egg) { removeEggSprite(egg); }
    }
    
    return true;
}


// ########## UPDATE ########## //
void GameLayer::update(float dt) {
    if (_state == GameState::init) { return; }
    
    if (_state == GameState::finished and _chicken->getPosition().x >= _visibleSize.width) {
        // goto game over scene with state: stage cleared
        auto gameOver = GameOverLayer::createScene(_score, true);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, gameOver));
    }
    
    if (_chicken->getState() == PlayerState::dying) {
        // goto game over scene with state: stage not cleared
        auto gameOver = GameOverLayer::createScene(_score, false);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, gameOver));
    }
    else {
        // chicken is alive and game state is not finished
        if (_background) { _background->update(_chicken->getVectorX()); }
        if (_layerTow) {
            _layerTow->update(_chicken->getVectorX());
            updateStageComplesion(_chicken->getVectorX());
        }
        if (_layerGround) { _layerGround->update(_chicken->getVectorX()); }
        if (_trampoline) { _trampoline->update(_chicken->getVectorX()); }
        if (_chicken) { _chicken->update(dt); }
        
        // if you start to draw trampoline then don't move your finger
        if (_trampoline and not _trampoline->isDrawingFinished()) {
            this->removeChild(_trampoline->getTrampoline());
            _trampoline = nullptr;
            
            drawNewTrampoline();
        }
        
        updateEggs(_chicken->getVectorX());
        
        // keep the camera on the player
//        focusOnCharacter();
        
        // update pause menu position, needed if camera movement enabled
        updatePauseMenuPosition();
        
        // update score label position, needed if camera movement enabled
        updateScoreLabelPosition();
        
        // stage finished
        if (_state == GameState::finishing and not _eggs.size()) {
//            CCLOG("Chicken Speed X %f", _chicken->getVectorX());
            _pauseMenu->setEnabled(false);
            
            _chicken->setState(PlayerState::start);

            // slow down in 2% decrease reate
            _chicken->applySpeedX( - _chicken->getVectorX() * 0.02);
            
            if (_chicken->getVectorX() <= 1) {
                endOfStage();
            }
        }
    }
}

void GameLayer::updateEggs(float playerSpeed) {
    for (int i = 0; i < _eggs.size(); ++i) {
        Sprite* e = _eggs.at(i);
        e->setPositionX(e->getPosition().x - EGG_SPEED * _visibleSize.width * playerSpeed);
        
        if (e->getPositionX() < -e->getContentSize().width) {
            this->removeChild(e);
            _eggs.erase(_eggs.begin() + i);
            
            --i; // handle new number one's position in next iteration
        }
    }
}

void GameLayer::updatePauseMenuPosition() {
    _pauseMenu->setPosition(_visibleSize.width / 2, _visibleSize.height * 0.95 - this->getPositionY());
}

void GameLayer::updateScoreLabel() {
    if (_scoreLabel) {
        _scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
    }
}

void GameLayer::updateScoreLabelPosition() {
    _scoreIcon->setPosition(_scoreIcon->getContentSize().width, _visibleSize.height * 0.9 - this->getPositionY());
    _scoreLabel->setPosition(_scoreIcon->getContentSize().width * 2.5, _visibleSize.height * 0.89 - this->getPositionY());
}

void GameLayer::updateStageComplesion(float speed) {
    _elapsedStage += speed * LAYER_TWO_SPEED * _visibleSize.width;
    if (_elapsedStage > _visibleSize.width * 0.5) {
        _stageLength -= _elapsedStage;
        CCLOG("Stage Remaining: %f", _stageLength);
        _elapsedStage = 0;
        
        // spawn eggs based on scrolled length
        spawnEgg();
        
        if (_stageLength <= 0) {
            _state = GameState::finishing;
        }
        // BASED ON NUMBER OF THIS ELAPSING, FINISH THE STAGE
    }
}



//////////////////////////////////////////////////////////////////

Scene* PauseLayer::createScene() {
    auto scene = Scene::create();
    auto layer = PauseLayer::create();
    auto resume = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseLayer::menuResumeCallback, layer));
    auto resumeMenu = Menu::create(resume, nullptr);
    resumeMenu->setNormalizedPosition(Vec2(0.5f,0.4f));
    layer->addChild(resumeMenu);
    scene->addChild(layer);
    return scene;
}
void PauseLayer::menuResumeCallback(Ref* pSender) {
    Director::getInstance()->popScene();
}













