#include "PauseLayer.h"

using namespace cocos2d;

Scene* PauseLayer::createScene() {
    auto scene = Scene::create();
    auto layer = PauseLayer::create();
    
    auto resume = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseLayer::menuResumeCallback, layer));
    auto resumeMenu = Menu::create(resume, nullptr);
    resumeMenu->setNormalizedPosition(Vec2(0.5f,0.6f));
    layer->addChild(resumeMenu);
    
    // add exit button only for android. apple might not approve exit(0)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto exit = MenuItemFont::create("Exit", CC_CALLBACK_1(PauseLayer::menuExitCallback, layer));
    auto exitMenu = Menu::create(exit, nullptr);
    exitMenu->setNormalizedPosition(Vec2(0.5f,0.4f));
    layer->addChild(exitMenu);
#endif
    
    scene->addChild(layer);
    return scene;
}

void PauseLayer::menuResumeCallback(Ref* pSender) {
    Director::getInstance()->popScene();
}

void PauseLayer::menuExitCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->end();
#endif
}



