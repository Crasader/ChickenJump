#ifndef __SPLASHSCREEN_LAYER_H__
#define __SPLASHSCREEN_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class SplashScreenLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScreenLayer);
    
// Added Functions
//    void update (float dt);
private:
    void GoToMainMenuLayer(float dt);
    
};

#endif // __SPLASHSCREEN_LAYER_H__
