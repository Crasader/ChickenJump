#ifndef __COLLECTABLE_SPRITE__
#define __COLLECTABLE_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Collectable {
public:
    Collectable(void);
    void spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables, int pattern);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    
    std::string const _imageFile = "egg1.png";
};


#endif /* __COLLECTABLE_SPRITE__ */
