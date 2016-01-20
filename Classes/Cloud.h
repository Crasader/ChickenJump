#ifndef __CLOUD_SPRITE__
#define __CLOUD_SPRITE__

#include <cocos2d.h>

class Cloud {
public:
    Cloud(void);
    void spawn(cocos2d::Layer* layer);
    
private:
    cocos2d::Sprite* _cloud;
    cocos2d::Layer* _layer;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
//    std::string const _spriteImage = "tree_br.png";
};


#endif /* __CLOUD_SPRITE__ */
