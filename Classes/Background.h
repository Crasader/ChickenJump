#ifndef __BACKGROUND_SPRITE__
#define __BACKGROUND_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Background {
public:
    Background(void);
    void createBackground(cocos2d::Layer* layer);
    void update(float dt);
    
private:
    Sprite* _background;
    std::string const _spriteImage = "background.png";
    Vec2 _origin;
    Size _visibleSize;
};



#endif /* __BACKGROUND_SPRITE__ */
