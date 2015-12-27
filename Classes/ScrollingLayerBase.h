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
    void createLayer(cocos2d::Layer* layer);
    void update(float speed);

    cocos2d::Sprite* _root;
    std::string _imageFile = "blank.png";
    BackgroundLayer _zOrder;
    std::vector<std::string> _scrollingImages;
    Stage _stage;
    
    // images for infinite stage
    std::string _imageFile1 = "blank.png";
    std::string _imageFile2 = "blank.png";
    std::string _imageFile3 = "blank.png";
    std::string _imageFile4 = "blank.png";
    std::string _imageFile5 = "blank.png";
    std::string _imageFile6 = "blank.png";
    
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
