#ifndef __SplashScreenLayer_H__
#define __SplashScreenLayer_H__

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
};

#endif // __SplashScreenLayer_H__
