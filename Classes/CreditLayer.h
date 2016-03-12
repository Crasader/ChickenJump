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
    
private:
    void addBackground();
    void addBackButton();
    void addGround();
    void backButtonClicked(cocos2d::Ref const* sender);
    
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
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __CREDIT_LAYER_H__
