#include "GameLayer.h"

#include "Cloud.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "Tree.h"

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
    
    // Spawn tree
//    this->schedule(schedule_selector(GameLayer::spawnTree), TREE_SPAWN_FREQUENCY * _visibleSize.width);

    // Spawn cloud
    this->schedule(schedule_selector(GameLayer::spawnCloud), CLOUD_SPAWN_FREQUENCY * _visibleSize.width);
    
    // Add Chicken
    _chicken = new Chicken();
    _chicken->createChicken(this);
    
    
    // Listen for touches
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    // Listen for contacts
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    // Create main loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::update(float dt) {
    if (_background) { _background->update(dt); }
    if (_layerTow) { _layerTow->update(dt); }
    if (_layerGround) { _layerGround->update(dt); }
    if (_chicken) { _chicken->update(dt); }
    if (_trampoline) { _trampoline->update(dt); }
}

void GameLayer::spawnTree(float dt) {
    Tree* tree = new Tree();
    tree->spawn(this);
}

void GameLayer::spawnCloud(float dt) {
    Cloud* cloud = new Cloud();
    cloud->spawn(this);
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

}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    if (touch->getLocation() == _lineStartPoint) {
        return;
    }
    
    _lineEndPoint = touch->getLocation();
    
    _trampoline = new Trampoline();
    _trampoline->createTrampoline(this, _lineStartPoint, _lineEndPoint);
}

bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {
    CCLOG("CONTACT");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    if ((a->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and b->getCollisionBitmask() == COLLISION_BITMASK_OBSTACLE) or
        (b->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and a->getCollisionBitmask() == COLLISION_BITMASK_OBSTACLE)) {
        
        // Jump only if the Chicken is within the visible size range
        if (_chicken->getChicken()->getPositionY() <= _visibleSize.height) {
            _chicken->setState(PlayerState::Jumping);
        }
    }
    
    if ((a->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and b->getCollisionBitmask() == COLLISION_BITMASK_GROUND) or
        (b->getCollisionBitmask() == COLLISION_BITMASK_CHICKEN and a->getCollisionBitmask() == COLLISION_BITMASK_GROUND)) {
        
        auto scene = MainMenuLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    return true;
}











