#ifndef __LAYER_TWO_SPRITE__
#define __LAYER_TWO_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class ScrollingSprite;
class Stage;

class LayerTwo {
public:
    LayerTwo(void);
    ~LayerTwo(void);
    void createLayerTwo(cocos2d::Layer* layer, Stage const& stage);
    void update(float speed);
    
private:
    std::vector<ScrollingSprite*> _scrollingSprites;
    std::string const _imageFile = "layertwo.png";
    cocos2d::Layer* _layer;
    
    Vec2 _origin;
    Size _visibleSize;
};



#endif /* __LAYER_TWO_SPRITE__ */
