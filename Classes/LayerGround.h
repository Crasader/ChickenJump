#ifndef __LAYER_GROUND_SPRITE__
#define __LAYER_GROUND_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class LayerGround {
public:
    LayerGround(void);
    void createLayerGround(cocos2d::Layer* layer);
    void update(float dt);
    
private:
    Sprite* _layerGround;
    std::string const _imageFile = "layerground.png";
    Vec2 _origin;
    Size _visibleSize;
};



#endif /* __LAYER_GROUND_SPRITE__ */
