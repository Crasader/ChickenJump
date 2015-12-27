#ifndef __SCROLLING_LAYER_BASE__
#define __SCROLLING_LAYER_BASE__

#include <cocos2d.h>

#include "Constants.h"
#include "Stage.h"
#include "StageStatus.h"

class ScrollingSprite;

class ScrollingLayerBase {
public:
    ScrollingLayerBase(void);
    virtual ~ScrollingLayerBase(void);
    void createLayer(cocos2d::Layer* layer, Stage const& stage);
    void update(float speed);

    cocos2d::Sprite* _root;
    std::string _imageFile = "blank.png";
    BackgroundLayer _zOrder;
    std::vector<std::string> _scrollingImages;
    Stage _stage;
    
private:
    std::queue<cocos2d::Sprite*> _scrollingSprites;
    cocos2d::Sprite* _newSprite;
    float _scrolled;
    float _checkpoint;
    float _diffx;
    int _currentLayerImageIndex;

    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    int _scrollingWindowSize; // 0 based index

};

#endif // __SCROLLING_LAYER_BASE__
