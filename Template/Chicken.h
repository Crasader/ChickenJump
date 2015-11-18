#ifndef __CHICKEN_SPRITE__
#define __CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Chicken {
public:
    Chicken(void);
    void createChicken(cocos2d::Layer* layer);
private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _sprite;
    
    std::string const _spriteImage = "";
};



#endif /* __CHICKEN_SPRITE__ */
