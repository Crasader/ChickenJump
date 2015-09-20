#ifndef __MAINMENU_LAYER_H__
#define __MAINMENU_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class MainMenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainMenuLayer);
    
private:
    void gotoGamePlayLayer(cocos2d::Ref* sender);
    void menuSelectFrance(cocos2d::Ref* sender);
    void menuSelectEngland(cocos2d::Ref* sender);
    void menuSelectSpain(cocos2d::Ref* sender);
    void menuSelectItaly(cocos2d::Ref* sender);
    void menuSelectItaly2(cocos2d::Ref* sender); //////// remove later
    void menuSelectGermany(cocos2d::Ref* sender);
    void menuSelectNetherlands(cocos2d::Ref* sender);
    void selectLevel(std::string level);
    bool _countryFrance;
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __MAINMENU_LAYER_H__
