#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class GameOverLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int score, bool isStageClear);

    virtual bool init();
    
    CREATE_FUNC(GameOverLayer);
    
private:
    void gotoGamePlayLayer(cocos2d::Ref* sender);
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
