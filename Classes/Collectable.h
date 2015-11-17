#ifndef __EGG_SPRITE__
#define __EGG_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Collectable {
public:
    Collectable(void);
    void spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables, int pattern);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _collectable;
    
    std::string const _imageFile = "egg1.png";
};


#endif /* __EGG_SPRITE__ */
