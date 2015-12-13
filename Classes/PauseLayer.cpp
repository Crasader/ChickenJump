#include "PauseLayer.h"

#include "GameLayer.h"
#include "BackButton.h"
#include "MainMenuLayer.h"

using namespace cocos2d;

static const std::string imageResume = "btn_resume.png";

bool PauseLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 190)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    this->setContentSize(Size(_visibleSize.width * 0.08, _visibleSize.height));
    this->setPosition(0, 0);
    
    
    
    // resume menu
    auto resume = MenuItemImage::create(imageResume, imageResume, CC_CALLBACK_1(GameLayer::resumeClicked, GameLayer::getInstance()));
    auto resumeMenu = Menu::create(resume, nullptr);
    resumeMenu->setNormalizedPosition(Vec2(0.5f,0.1f));
    this->addChild(resumeMenu);
    
    // goto main menu
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    mainMenu->createBackButton(this);
    mainMenu->setPosition(Vec2(_visibleSize.width * 0.04, resume->getContentSize().height * 2.5));
    

    
    // add exit button only for android. apple might not approve exit(0)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto exit = MenuItemFont::create("Exit", CC_CALLBACK_1(PauseLayer::menuExitCallback, this));
    auto exitMenu = Menu::create(exit, nullptr);
    exitMenu->setNormalizedPosition(Vec2(0.5f,0.40f));
    this->addChild(exitMenu);
#endif
    
    return true;
}

void PauseLayer::menuExitCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->end();
#endif
}



