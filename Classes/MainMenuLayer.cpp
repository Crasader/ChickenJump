#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"

using namespace cocos2d;

Scene* MainMenuLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    MainMenuLayer *layer = MainMenuLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuLayer::init()
{
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // 2. origin & window size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add background
    auto background = Sprite::create("blank.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);
    
    // transition to GameLayer
    auto playItem = MenuItemImage::create("play.png", "playclicked.png",
                                          CC_CALLBACK_1(MainMenuLayer::GoToGamePlayLayer, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void MainMenuLayer::GoToGamePlayLayer(cocos2d::Ref* sender)
{
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



