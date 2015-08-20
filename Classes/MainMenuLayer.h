#ifndef __MainMenuLayer_H__
#define __MainMenuLayer_H__

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
};

#endif // __MainMenuLayer_H__
