#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class HomeLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeLayer);
    
private:
    void addBackground();
    void addGround();
    void addPlayMenu();
    void gotoMainMenuLayer(cocos2d::Ref* sender);
    void writeFreshStageStats();
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __HOMELAYER_H__
