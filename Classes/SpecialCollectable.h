#ifndef __SPECIAL_COLLECTABLE_SPRITE__
#define __SPECIAL_COLLECTABLE_SPRITE__

#include <cocos2d.h>

class SpecialCollectable {
public:
    SpecialCollectable(void);
    void spawn(cocos2d::Layer* layer, std::vector<cocos2d::Sprite*>& specialCollectables);
    
private:
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    std::string const _imageFile = "egg3.png";
};


#endif /* __SPECIAL_COLLECTABLE_SPRITE__ */
