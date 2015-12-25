#ifndef __SCROLLING_SPRITE__
#define __SCROLLING_SPRITE__

#include <cocos2d.h>
#include "Constants.h"

class ScrollingSprite {
public:
    // 0 based index: By adding multiple images we build our scrolling stage. this index tells which position the image should sit.
    ScrollingSprite(std::string const& imageFile, cocos2d::Layer* layer, BackgroundLayer const z, int const index);
    cocos2d::Sprite* getSprite();
    void update(float speed);
private:
    cocos2d::Sprite* _sprite;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};

#endif // __SCROLLING_SPRITE__
