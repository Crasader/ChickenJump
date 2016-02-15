
#ifndef __BACKBUTTON__
#define __BACKBUTTON__

#include <cocos2d.h>

#include "Constants.h"

template <typename T>
class BackButton {
public:
    BackButton(void) {
        _origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    }
    
    void createBackButton(cocos2d::Layer* layer) {
        if (not layer) { return; }
        
        _backItem = cocos2d::MenuItemImage::create(_image, _imageClicked, CC_CALLBACK_1(BackButton::goBack, this));
        if (not _backItem) { return; }
        _backMenu = cocos2d::Menu::create(_backItem, NULL);
        layer->addChild(_backMenu, BackgroundLayer::layerGround);
    }
    
    cocos2d::Size getContentSize() {
        if (not _backItem) { return cocos2d::Size(); }
        return _backItem->getContentSize();
    }
    
    void setPosition(cocos2d::Vec2 position) {
        if (not _backMenu) { return; }
        _backMenu->setPosition(position);
    }
    
    void setNormalizedPosition(cocos2d::Vec2 position) {
        if (not _backItem) { return; }
        _backItem->setNormalizedPosition(position);
    }
    
    void goBack(cocos2d::Ref const* ref) {
        auto scene = T::createScene();
        if (not scene) { return; }
        if (cocos2d::Director::getInstance()->isPaused()) {
            cocos2d::Director::getInstance()->resume();
        }
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;

    cocos2d::Menu* _backMenu;
    cocos2d::MenuItemImage* _backItem;
    
    const std::string _image = "btn_back.png";
    const std::string _imageClicked = "btn_backclicked.png";
};

#endif // __BACKBUTTON__
