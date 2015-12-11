
#ifndef __BACKBUTTON__
#define __BACKBUTTON__

#include <cocos2d.h>

#include "Constants.h"

using namespace cocos2d;

template <typename T>
class BackButton {
public:
    BackButton(void) {
        _origin = Director::getInstance()->getVisibleOrigin();
        _visibleSize = Director::getInstance()->getVisibleSize();
    }
    
    void createBackButton(Layer* layer) {
        if (not layer) { return; }
        
        _backItem = MenuItemImage::create(_image, _imageClicked, CC_CALLBACK_1(BackButton::goBack, this));
        if (not _backItem) { return; }
        _backMenu = Menu::create(_backItem, NULL);
        layer->addChild(_backMenu, BackgroundLayer::layerGround);
    }
    
    Size getContentSize() {
        if (not _backItem) { return Size(); }
        return _backItem->getContentSize();
    }
    
    void setPosition(Vec2 position) {
        if (not _backMenu) { return; }
        _backMenu->setPosition(position);
    }
    
    void goBack(Ref* ref) {
        auto scene = T::createScene();
        if (not scene) { return; }
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    Vec2 _origin;
    Size _visibleSize;

    Menu* _backMenu;
    MenuItemImage* _backItem;
    
    const std::string _image = "btn_back.png";
    const std::string _imageClicked = "btn_backclicked.png";
};

#endif // __BACKBUTTON__
