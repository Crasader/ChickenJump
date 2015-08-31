#include "GameLayer.h"

#include "Cloud.h"
#include "Constants.h"
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
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255))) {
        return false;
    }
    
    // 2. origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("GameLayer _visibleSize width %f, height %f", _visibleSize.width, _visibleSize.height);

    
    // add a physics body box around the screen
    auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    

    // add background
    _background = new Background();
    _background->createBackground(this);
    
    // add layerTwo
    _layerTow = new LayerTwo();
    _layerTow->createLayerTwo(this);
    
    // add layerGround
    _layerGround = new LayerGround();
    _layerGround->createLayerGround(this);
    
    // spawn tree
//    this->schedule(schedule_selector(GameLayer::spawnTree), TREE_SPAWN_FREQUENCY * _visibleSize.width);

    // spawn cloud
    this->schedule(schedule_selector(GameLayer::spawnCloud), CLOUD_SPAWN_FREQUENCY * _visibleSize.width);
    
    // add Chicken
    _chicken = new Chicken();
    _chicken->createChicken(this);
    
    
    //listen for touches
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    //create main loop
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
    
    // Jump only if the Chicken is within the visible size range
    if (_chicken->getChicken()->getPositionY() <= _visibleSize.height) {
        _chicken->setState(PlayerState::Jumping);
    }

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













