#ifndef __LAYER_BACKGROUND__
#define __LAYER_BACKGROUND__

#include <cocos2d.h>

#include "ScrollingLayerBase.h"

class LayerBackground : public ScrollingLayerBase {
public:
    LayerBackground(Stage const& stage);
    virtual ~LayerBackground(void);
};



#endif // __LAYER_BACKGROUND__
