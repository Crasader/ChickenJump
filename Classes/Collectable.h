#ifndef __COLLECTABLE_SPRITE__
#define __COLLECTABLE_SPRITE__

#include <cocos2d.h>

class Collectable {
public:
    Collectable(void);
    void spawn(cocos2d::Layer* layer, std::vector<cocos2d::Sprite*>& collectables, int pattern);
    
private:
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    std::string const _imageFile = "egg1.png";
};


#endif /* __COLLECTABLE_SPRITE__ */
