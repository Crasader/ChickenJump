#ifndef __CREDIT_LAYER_H__
#define __CREDIT_LAYER_H__

#include "cocos2d.h"

class CreditHUD;

class CreditLayer : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CreditLayer);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

private:
    void addBackground();
    void addGround();
    
    CreditHUD* _creditHUD;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


//
// Credit HUD
//
class CreditHUD : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(CreditHUD);
    
private:
    void addBackButton();
    void backButtonClicked(cocos2d::Ref const* sender);

    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __CREDIT_LAYER_H__
