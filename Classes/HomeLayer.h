#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"

#include "CreditLayer.h"
#include "FloatingChicken.h"
#include "SettingsMenuHUD.h"

using namespace cocos2d;

class HomeLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeLayer);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

    void update(float dt);
    
private:
    void addBackground();
    void addCreditMenu();
    void addFlyingChickens();
    void addGround();
    void addLogo();
    void addPlayMenu();
    void creditButtonClicked(cocos2d::Ref const* sender);
    void gotoMainMenuLayer(cocos2d::Ref const* sender);
    void initStage();
    
    Sprite* _logo;
    
    FloatingChicken* _flyingChicken1;
    FloatingChicken* _flyingChicken2;
    FloatingChicken* _flyingChicken4;
    
    SettingsMenuHUD* _settingsHUD;
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __HOMELAYER_H__
