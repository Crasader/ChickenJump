#include "GameLayer.h"
#include "Tree.h"
#include "Cloud.h"
#include "Constants.h"

using namespace cocos2d;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
//    auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    CCLOG("--- GameLayer _visibleSize width %f, height %f", _visibleSize.width, _visibleSize.height);

    
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
    _background->update(dt);
    _layerTow->update(dt);
    _layerGround->update(dt);
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
    
    _chicken->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 200));
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event) {
    _lineEndPoint = touch->getLocation();
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    _lineEndPoint = touch->getLocation();
    
    float xDist = (_lineEndPoint.x - _lineStartPoint.x);
    float yDist = (_lineEndPoint.y - _lineStartPoint.y);
    float distance = sqrt((xDist * xDist) + (yDist * yDist)); // distance = √(x^2 + y^2)
    
    // create a static PhysicsBody
    auto physicsBody = PhysicsBody::createBox(Size(distance, 10.0f ), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(false);
    
    // create DrawNode for drawing line instead of Sprite
//    {
//        auto drawNode = DrawNode::create();
//        drawNode->drawSegment(_lineStartPoint, _lineEndPoint, 10, Color4F::GRAY);
//
//     sprite will use physicsBody
//        physicsBody->setPositionOffset(Vec2(_lineStartPoint.x + std::abs(_lineEndPoint.x - _lineStartPoint.x) / 2, _lineEndPoint.y));
//        drawNode->setPhysicsBody(physicsBody);
//        this->addChild(drawNode, BackgroundLayer::layerTwo);
//    }
    
    // create a Sprite instead of DrawNode
    {
        auto sprite = Sprite::create("land.png");
        sprite->setPosition(Vec2(_lineStartPoint.x, _lineStartPoint.y));
        sprite->setAnchorPoint(Vec2(0, 0));
        
        // sprite will use physicsBody
        physicsBody->setPositionOffset(Vec2((_lineEndPoint.x - _lineStartPoint.x) / 2, 0));
        sprite->setPhysicsBody(physicsBody);
        this->addChild(sprite, BackgroundLayer::layerChicken);
    }
    
}













