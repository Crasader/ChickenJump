#ifndef __MAINMENU_LAYER_H__
#define __MAINMENU_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class StageStat;

class MainMenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainMenuLayer);
    
private:
    void addBackground();
    void gotoGamePlayLayer(cocos2d::Ref* sender, StageStat& stage);
    void menuSelectSgate(cocos2d::Ref* sender, StageStat& stage);
    void selectLevel(std::string level);
    bool _countryFrance;
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __MAINMENU_LAYER_H__
