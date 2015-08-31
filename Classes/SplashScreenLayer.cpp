#include "SplashScreenLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"

using namespace cocos2d;

Scene* SplashScreenLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    SplashScreenLayer *layer = SplashScreenLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScreenLayer::init()
{
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // 2. origin & window size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // schedule SplashScreen and Transition to MainMenu
    this->scheduleOnce(schedule_selector(SplashScreenLayer::GoToMainMenuLayer), DISPLAY_TIME_SPLASH_SCREEN);
    auto backgroundSprite = Sprite::create("splashscreen.png");
    CCLOG("splashscreen.width,height %f, %f", backgroundSprite->getContentSize().width, backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    return true;
}

void SplashScreenLayer::GoToMainMenuLayer(float dt)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



