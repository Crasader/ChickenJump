#ifndef __TRAMPOLINE_SPRITES__
#define __TRAMPOLINE_SPRITES__

#include <cocos2d.h>

using namespace cocos2d;

class Trampoline {
public:
    Trampoline(void);
    void createTrampoline(cocos2d::Layer* layer, Vec2 lineStartPoint, Vec2 lineEndPoint);
    Sprite* getTrampoline();
    void update(float dt);
    
private:
    Sprite* _trampoline;
    std::string const _imageFile = "trampoline.png";
    Vec2 _origin;
    Size _visibleSize;
};



#endif /* __TRAMPOLINE_SPRITES__ */
