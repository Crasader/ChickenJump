#ifndef __TRAMPOLINE_SPRITES__
#define __TRAMPOLINE_SPRITES__

#include <cocos2d.h>

class Trampoline {
public:
    Trampoline(void);
    void createTrampoline(cocos2d::Layer* layer, cocos2d::Vec2 lineStartPoint, cocos2d::Vec2 lineEndPoint);
    cocos2d::Sprite* getTrampoline() const;
    void update(float speed);

    static bool isDrawingOngoing;

private:
    cocos2d::Sprite* _trampoline;
    cocos2d::Sprite* _spriteToKnowContentWidth;
    float _trampolineWidth;
    std::string const _imageFile = "trampoline.png";
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};



#endif /* __TRAMPOLINE_SPRITES__ */
