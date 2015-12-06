#ifndef __SPECIAL_COLLECTABLE_SPRITE__
#define __SPECIAL_COLLECTABLE_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class SpecialCollectable {
public:
    SpecialCollectable(void);
    void spawn(cocos2d::Layer* layer, std::vector<Sprite*>& specialCollectables);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    
    std::string const _imageFile = "egg3.png";
};


#endif /* __SPECIAL_COLLECTABLE_SPRITE__ */
