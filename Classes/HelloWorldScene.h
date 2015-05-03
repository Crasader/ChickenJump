#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void addMonster(float dt);
    
    // touch began callback
    bool onTouchBegan(Touch *touch, Event *unused_event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    Sprite *_player;
};

#endif // __HELLOWORLD_SCENE_H__
