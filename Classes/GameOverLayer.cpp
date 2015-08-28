#include "GameOverLayer.h"

using namespace cocos2d;

Scene* GameOverLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameOverLayer *layer = GameOverLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // 2. origin & window size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return true;
}





