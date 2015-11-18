#ifndef __LAYER_TWO_SPRITE__
#define __LAYER_TWO_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class LayerTwo {
public:
    LayerTwo(void);
    void createLayerTwo(cocos2d::Layer* layer);
    void update(float speed);
    
private:
    Sprite* _layerTow;
    std::string const _imageFile = "layertwo.png";
    Vec2 _origin;
    Size _visibleSize;
};



#endif /* __LAYER_TWO_SPRITE__ */
