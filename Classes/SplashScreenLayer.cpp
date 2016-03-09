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
    
    loadResources();
    
    return true;
}

void SplashScreenLayer::gotoHomeLayer(float dt)
{
    auto scene = HomeLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void SplashScreenLayer::loadResources() {
    auto textureCache = Director::getInstance()->getTextureCache();
    
    // We don't need to get the root directory from FileUtility, because at this moment we already have "resource_**/" in search_path
    
    // INFINITE Stage resources
    textureCache->addImageAsync("INFINITE/background1.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/background2.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/background3.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/background4.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/background5.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/background6.png", [](Texture2D *res){  } );

    textureCache->addImageAsync("INFINITE/foreground1.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/foreground2.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/foreground3.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/foreground4.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/foreground5.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE/foreground6.png", [](Texture2D *res){  } );

    // Button Clicked
    textureCache->addImageAsync("UK_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("IT_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("FR_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("DE_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("SP_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("NL_clicked.png", [](Texture2D *res){  } );
    textureCache->addImageAsync("INFINITE_clicked.png", [](Texture2D *res){  } );

}



