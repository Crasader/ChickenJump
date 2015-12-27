#ifndef __LAYER_GROUND__
#define __LAYER_GROUND__

#include <cocos2d.h>

#include "ScrollingLayerBase.h"

class LayerGround : public ScrollingLayerBase {
public:
    LayerGround(Stage& stage);
    virtual ~LayerGround();
};



#endif // __LAYER_GROUND__
