#include "SplashScreenLayer.h"

#include "Constants.h"
#include "HomeLayer.h"
#include "MainMenuLayer.h"

using namespace cocos2d;

Scene* SplashScreenLayer::createScene()
{
    auto scene = Scene::create();
    
    SplashScreenLayer *layer = SplashScreenLayer::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool SplashScreenLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // schedule SplashScreen and Transition to MainMenu
    this->scheduleOnce(schedule_selector(SplashScreenLayer::gotoHomeLayer), DISPLAY_TIME_SPLASH_SCREEN);
    auto backgroundSprite = Sprite::create("splashscreen.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    return true;
}

void SplashScreenLayer::gotoHomeLayer(float dt)
{
    auto scene = HomeLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



