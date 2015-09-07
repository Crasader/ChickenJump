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

    
    // Add a physics body box around the screen
    {
        auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
        edgeBody->setCollisionBitmask(COLLISION_BITMASK_GROUND);
        edgeBody->setContactTestBitmask(true);
        
        auto edgeNode = Node::create();
        edgeNode->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
        edgeNode->setPhysicsBody(edgeBody);
        this->addChild(edgeNode);
    }

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
    
    // Increase speed
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
    _score = 0;
    std::string scoreStr = String::createWithFormat("%d", _score)->getCString();
    _scoreLabel = Label::createWithTTF(scoreStr, "Marker Felt.ttf", _visibleSize.height * SCORE_FONT_SIZE);
    if (_scoreLabel) {
        _scoreLabel->setColor(Color3B::WHITE);
        _scoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.9 + _origin.y);
        this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
    }
    
    // Create main loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::update(float dt) {
    if (_background) { _background->update(_chicken->getSpeedX()); }
    
    if (_layerTow) { _layerTow->update(_chicken->getSpeedX()); }
    if (_layerGround) { _layerGround->update(_chicken->getSpeedX()); }
    if (_trampoline) { _trampoline->update(_chicken->getSpeedX()); }
    
    if (_chicken) { _chicken->update(dt); }
    
    updateEggs(_chicken->getSpeedX());
}

void GameLayer::spawnEgg(float dt) {
    Egg* egg = new Egg();
    egg->spawn(this, _eggs);
}

void GameLayer::spawnCloud(float dt) {
    Cloud* cloud = new Cloud();
    cloud->spawn(this);
}

void GameLayer::updateEggs(float playerSpeed) {
    for (auto it = _eggs.begin(); it != _eggs.end(); ++it) {
        (*it)->setPositionX((*it)->getPosition().x - LAYER_GROUND_SPEED * _visibleSize.width * playerSpeed);
        
        if ((*it)->getPositionX() < -(*it)->getContentSize().width) {
            this->removeChild(*it);
            _eggs.erase(it);
        }
    }
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
    
    // Create new trampoline
    _trampoline = new Trampoline();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    if (_trampoline) { _trampoline->setDrawingFinished(true); }
}

bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {
//    CCLOG("CONTACT");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    float chickenPositionY = _chicken->getChicken()->getPositionY();
    
    // collision between chicken and trampoline
    if ((a->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and b->getCollisionBitmask() == COLLISION_BITMASK_TRAMPOLINE)) {
        auto trampoline = (Sprite*)contact.getShapeB()->getBody()->getNode();
        float trampolinePositionY = trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY();
        
        if (chickenPositionY > trampolinePositionY and
            _chicken->getState() == PlayerState::Falling) {

            _chicken->setState(PlayerState::Jumping);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.wav");
            speedUp(0);
        }
        else if (trampolinePositionY > chickenPositionY and
                 _chicken->getState() == PlayerState::Jumping) {

            _chicken->setState(PlayerState::Falling);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bump.wav");
        }
    }
    // collision between trampoline and chicken
    if ((b->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and a->getCollisionBitmask() == COLLISION_BITMASK_TRAMPOLINE)) {
        auto trampoline = (Sprite*)contact.getShapeA()->getBody()->getNode();
        float trampolinePositionY = trampoline->getPositionY() + _trampoline->getTrampoline()->getPositionY();
        
        if (chickenPositionY > trampolinePositionY and
            _chicken->getState() == PlayerState::Falling) {

            _chicken->setState(PlayerState::Jumping);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.wav");
            speedUp(0);
        }
        else if (trampolinePositionY > chickenPositionY and
                 _chicken->getState() == PlayerState::Jumping) {

            _chicken->setState(PlayerState::Falling);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bump.wav");
        }
    }
    
    // collision between chicken and screen edges
    if ((a->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and b->getCollisionBitmask() == COLLISION_BITMASK_GROUND) or
        (b->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and a->getCollisionBitmask() == COLLISION_BITMASK_GROUND)) {
        
        auto gameOver = GameOverLayer::createScene(_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, gameOver));
    }
    
    // collision between chicken and eggs
    if (a->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and b->getCollisionBitmask() == COLLISION_BITMASK_EGG) {
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
    else if (b->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and a->getCollisionBitmask() == COLLISION_BITMASK_EGG) {
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












