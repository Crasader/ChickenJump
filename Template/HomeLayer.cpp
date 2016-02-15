#include "HomeLayer.h"

using namespace cocos2d;

Scene* HomeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = HomeLayer::create();
    scene->addChild(layer);

    return scene;
}

bool HomeLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    return true;
}

