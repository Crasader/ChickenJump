#ifndef __MAINMENU_LAYER_H__
#define __MAINMENU_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class MainMenuLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuLayer);
    
    // Added Functions
//    void update (float dt);
    
private:
    void goToGamePlayLayer(cocos2d::Ref* sender);
    void toggleCountry(cocos2d::Ref* sender);
    bool _countryFrance;
};

#endif // __MAINMENU_LAYER_H__
