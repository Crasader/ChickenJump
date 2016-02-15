#ifndef __LAYER_TWO_SPRITE__
#define __LAYER_TWO_SPRITE__

#include <cocos2d.h>

#include "ScrollingLayerBase.h"

class LayerTwo : public ScrollingLayerBase {

public:
    LayerTwo(Stage const& stage);
    virtual ~LayerTwo(void);
};

#endif /* __LAYER_TWO_SPRITE__ */
