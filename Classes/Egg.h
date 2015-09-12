#ifndef __EGG_SPRITE__
#define __EGG_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Egg {
public:
    Egg(void);
    void spawn(cocos2d::Layer* layer, std::vector<Sprite*>& eggs, int pattern);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _egg;
    
    std::string const _imageFile = "egg1.png";
};


#endif /* __EGG_SPRITE__ */
