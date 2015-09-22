#include "PauseLayer.h"

#include "GameLayer.h"

using namespace cocos2d;

bool PauseLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 192)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    this->setContentSize(Size(_visibleSize.width * 0.08, _visibleSize.height));
    this->setPosition(0, 0);
    
    auto resume = MenuItemImage::create("resume.png", "resume.png", CC_CALLBACK_1(GameLayer::resumeClicked, GameLayer::getInstance()));
    auto resumeMenu = Menu::create(resume, nullptr);
    resumeMenu->setNormalizedPosition(Vec2(0.5f,0.1f));
    this->addChild(resumeMenu);
    
    // add exit button only for android. apple might not approve exit(0)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto exit = MenuItemFont::create("Exit", CC_CALLBACK_1(PauseLayer::menuExitCallback, this));
    auto exitMenu = Menu::create(exit, nullptr);
    exitMenu->setNormalizedPosition(Vec2(0.5f,0.4f));
    this->addChild(exitMenu);
#endif
    
    return true;
}

void PauseLayer::menuExitCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->end();
#endif
}



