#ifndef __SPLASHSCREEN_LAYER_H__
#define __SPLASHSCREEN_LAYER_H__

#include <cocos2d.h>

class SplashScreenLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(SplashScreenLayer);
    
private:
    void gotoHomeLayer(float dt);
    void loadResources();
};

#endif // __SPLASHSCREEN_LAYER_H__
