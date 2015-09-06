#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class GameOverLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(unsigned int score);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverLayer);
    
    // Added Functions
//    void update (float dt);
    
private:
    void gotoGamePlayLayer(cocos2d::Ref* sender);
    void toggleCountry(cocos2d::Ref* sender);
    bool _countryFrance;

    Vec2 _origin;
    Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
