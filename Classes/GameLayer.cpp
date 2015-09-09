#include "GameLayer.h"

#include "Cloud.h"
#include "Constants.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "Egg.h"

using namespace cocos2d;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
//    auto scene = Scene::create();
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
    CCLOG("GameLayer _visibleSize width %f, height %f", _visibleSize.width, _visibleSize.height);

    _isPaused = false;
    
    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_visibleSize.width * 0.5f, _visibleSize.height * 0.5f));
    this->addChild(bg, BackgroundLayer::layerBG);

    // Add background
    _background = new Background();
    _background->createBackground(this);
    
    // Add layerTwo
    _layerTow = new LayerTwo();
    _layerTow->createLayerTwo(this);
    
    // Add layerGround
    _layerGround = new LayerGround();
    _layerGround->createLayerGround(this);
    
    // Spawn cloud
    this->schedule(schedule_selector(GameLayer::spawnCloud), CLOUD_SPAWN_FREQUENCY * _visibleSize.width);
    
    // Add chicken
    _chicken = new Chicken();
    _chicken->createChicken(this);
    
    // Increase speed periodicaly
//    this->schedule(schedule_selector(GameLayer::speedUp), SPEED_CHANGE_FREQUENCY * _visibleSize.width);
    
    // Spawn egg
    this->schedule(schedule_selector(GameLayer::spawnEgg), EGG_SPAWN_FREQUENCY * _visibleSize.width);
    
    
    // Listen for touches
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    // Listen for collision
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // Score Label
    {
        _score = 0;
        _scoreIcon = Sprite::create("egg.png");
        _scoreIcon->setAnchorPoint(Vec2(0, 0));
//        _scoreIcon->setPosition(_scoreIcon->getContentSize().width, _visibleSize.height * 0.87);
        this->addChild(_scoreIcon, BackgroundLayer::layerChicken);
        
        std::string scoreStr = String::createWithFormat("%d", _score)->getCString();
        _scoreLabel = Label::createWithTTF(scoreStr, "Marker Felt.ttf", _visibleSize.height * SCORE_FONT_SIZE);
        if (_scoreLabel) {
            _scoreLabel->setColor(Color3B::WHITE);
            _scoreLabel->setAnchorPoint(Vec2(0, 0));
//            _scoreLabel->setPosition(_scoreIcon->getContentSize().width * 2.5, _visibleSize.height * 0.86);
            this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
        }
    }
    
    // Pause/Resume toggle
    {
        MenuItem* pause = MenuItemImage::create("pause.png", "pause.png");
        MenuItem* resume = MenuItemImage::create("resume.png", "resume.png");
        MenuItemToggle* pauseToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameLayer::togglePause, this), pause, resume, NULL);
        _pauseToggleMenu = Menu::create(pauseToggleItem, NULL);
        _pauseToggleMenu->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height * 0.95)); // position updated in update fn
        this->addChild(_pauseToggleMenu, BackgroundLayer::layerChicken);
    }
    
    // Activate main update loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::update(float dt) {
    if (_isPaused) { return; }
    
    if (_chicken->getState() == PlayerState::Dying) {
        auto gameOver = GameOverLayer::createScene(_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, gameOver));
    }
    else {
        if (_background) { _background->update(_chicken->getSpeedX()); }
        if (_layerTow) { _layerTow->update(_chicken->getSpeedX()); }
        if (_layerGround) { _layerGround->update(_chicken->getSpeedX()); }
        if (_trampoline) { _trampoline->update(_chicken->getSpeedX()); }
        if (_chicken) { _chicken->update(dt); }
        
        updateEggs(_chicken->getSpeedX());
        
        // keep the camera on the player
//        if(_chicken->getChicken()->getPositionY() > _visibleSize.height * 0.6f) {
//            this->setPositionY( (_visibleSize.height * 0.6f - _chicken->getChicken()->getPositionY()) * 0.8f);
//        } else {
//            this->setPositionY(0);
//        }
        
        // update pause menu
        _pauseToggleMenu->setPosition(_visibleSize.width / 2, _visibleSize.height * 0.95 - this->getPositionY());
        
        // update score label
        _scoreIcon->setPosition(_scoreIcon->getContentSize().width, _visibleSize.height * 0.9 - this->getPositionY());
        _scoreLabel->setPosition(_scoreIcon->getContentSize().width * 2.5, _visibleSize.height * 0.89 - this->getPositionY());
        
        //
        
    }
}

void GameLayer::updateEggs(float playerSpeed) {
    for (int i = 0; i < _eggs.size(); ++i) {
        Sprite* e = _eggs.at(i);
        e->setPositionX(e->getPosition().x - LAYER_GROUND_SPEED * _visibleSize.width * playerSpeed);
        
        if (e->getPositionX() < -e->getContentSize().width) {
            this->removeChild(e);
            _eggs.erase(_eggs.begin() + i);
        }
    }
}

void GameLayer::spawnEgg(float dt) {
    Egg* egg = new Egg();
    egg->spawn(this, _eggs);
}

void GameLayer::spawnCloud(float dt) {
    Cloud* cloud = new Cloud();
    cloud->spawn(this);
}

void GameLayer::speedUp(float dt) {
//    _chicken->increaseSpeedX();
    float xDist = (_lineEndPoint.x - _lineStartPoint.x);
    float yDist = (_lineEndPoint.y - _lineStartPoint.y);
    
    if (_lineStartPoint.x > _lineEndPoint.x) {
        xDist = (_lineStartPoint.x - _lineEndPoint.x);
        yDist = (_lineStartPoint.y - _lineEndPoint.y);
    }

    float degree = atan2(yDist, xDist) * 180 / PI;
    
    _chicken->changeSpeedX(-degree * CUSTOM_ACCELERATION);
}

void GameLayer::togglePause(cocos2d::Ref* layer) {
    _isPaused = not _isPaused;
    if (_isPaused) {
        Director::getInstance()->pause();
    }
    else {
        Director::getInstance()->resume();
    }
}


// ########## TOUCH EVENTS ########## //
bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
    _lineStartPoint = touch->getLocation();
    _lineEndPoint = _lineStartPoint;

    // Remove old trampoline
    if (_trampoline) {
        this->removeChild(_trampoline->getTrampoline());
        _trampoline = nullptr;
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event) {
    if (touch->getLocation() == _lineStartPoint) { return; }
    if (touch->getLocation().distance(_lineStartPoint) < 30) { return; } // 30 is just trampoline's sprites twice width
    
    _lineEndPoint = touch->getLocation();
    
    // Remove old trampoline
    if (_trampoline) {
        this->removeChild(_trampoline->getTrampoline());
        _trampoline = nullptr;
    }
    
    // don't draw trampoline above the screen height
    if (_lineStartPoint.y - this->getPositionY() > _visibleSize.height) { return; }
    
    // Draw new trampoline
    _trampoline = new Trampoline();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    if (_trampoline) { _trampoline->setDrawingFinished(true); }
}


// ########## COLLISION HANDLING ########## //
bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {
    CCLOG("CONTACT");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    float chickenPositionY = _chicken->getChicken()->getPositionY();
    
    // collision between chicken and trampoline
    if ((a->getCategoryBitmask() == 1 and b->getCategoryBitmask() == 2)) {
        auto trampoline = (Sprite*)contact.getShapeB()->getBody()->getNode();
        float trampolinePositionY = trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY();
        
        if (chickenPositionY > trampolinePositionY and
            _chicken->getState() == PlayerState::Falling) {

            _chicken->setState(PlayerState::Jumping);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.wav");
            speedUp(0);
        }
    }
    // collision between trampoline and chicken
    else if ((a->getCategoryBitmask() == 2 and b->getCategoryBitmask() == 1)) {
        auto trampoline = (Sprite*)contact.getShapeA()->getBody()->getNode();
        float trampolinePositionY = trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY();
        
        if (chickenPositionY > trampolinePositionY and
            _chicken->getState() == PlayerState::Falling) {

            _chicken->setState(PlayerState::Jumping);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.wav");
            speedUp(0);
        }    }
    
    
    // collision between chicken and eggs
    if (a->getCategoryBitmask() == 1 and b->getCategoryBitmask() == 4) {
        _score ++;
        if (_scoreLabel) {
            _scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
        }
        
        auto egg = (Sprite*)contact.getShapeB()->getBody()->getNode();
        // Remove colided egg
        if (egg) {
            this->removeChild(egg);
            if (std::find(_eggs.begin(), _eggs.end(), egg) != _eggs.end()) {
                _eggs.erase(std::find(_eggs.begin(), _eggs.end(), egg));
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup_coin.wav");
            }
        }
    }
    // collision between eggs and chicken
    else if (a->getCategoryBitmask() == 4 and b->getCategoryBitmask() == 1) {
        _score ++;
        if (_scoreLabel) {
            _scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
        }
        
        auto egg = (Sprite*)contact.getShapeA()->getBody()->getNode();
        // Remove colided egg
        if (egg) {
            this->removeChild(egg);
            if (std::find(_eggs.begin(), _eggs.end(), egg) != _eggs.end()) {
                _eggs.erase(std::find(_eggs.begin(), _eggs.end(), egg));
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup_coin.wav");
            }
        }
    }
    
    return true;
}












