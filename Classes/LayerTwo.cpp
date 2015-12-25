#include "LayerTwo.h"

#include "Constants.h"
#include "ScrollingSprite.h"
#include "Stage.h"
#include "StageStatus.h"

static int _start;
static int _end;
static int _diffx;
static int _scrollingWindowSize = 2; // 0 based index

LayerTwo::LayerTwo(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

LayerTwo::~LayerTwo(void) {
    for (std::vector<ScrollingSprite*>::iterator i = _scrollingSprites.begin(); i != _scrollingSprites.end(); ++i) {
        delete *i;
    }
}

void LayerTwo::createLayerTwo(cocos2d::Layer* layer, Stage const& stage) {
    if (not layer) { return; }
    
    _layer = layer;
    _start = 0;
    _end = _start + _scrollingWindowSize;
    
    // Use 3 images to implement scrolling (unless its the infinite stage)
    int numberOfScrollingSprite = 3;
    for (int i = 0; i < numberOfScrollingSprite; ++i) {
        ScrollingSprite* ss = new ScrollingSprite(_imageFile, layer, BackgroundLayer::layerTwo, i);
        _scrollingSprites.push_back(ss);
    }

    if (stage.getName() == StageStatus::infinite) {
        // ADD MORE SPRITES FOR THE INFINITE STAGE
        numberOfScrollingSprite = 12; // additional sprites for the infinite stage
        for (int i = 0; i < numberOfScrollingSprite; ++i) {
            ScrollingSprite* ss = new ScrollingSprite("DE/layertwo.png", layer, BackgroundLayer::layerTwo, _scrollingWindowSize);
            _scrollingSprites.push_back(ss);
        }
    }
    
}

void LayerTwo::update(float speed) {
    if (_scrollingSprites.empty()) { return; }
    
    float scrollingSpeed = LAYER_TWO_SPEED * _visibleSize.width * speed;
    
    // scroll
    for (int i = _start; i <= _end; ++i) {
        _scrollingSprites.at(i % _scrollingSprites.size())->update(scrollingSpeed);
    }
    
    // check if the front scrolling image has scrolled out
    if (_scrollingSprites.at(_start)->getSprite()->getPositionX() < -_visibleSize.width * 0.5) {

        Sprite* frontSprite = _scrollingSprites.at(_start)->getSprite();
        if (not frontSprite) { return; }

        Sprite* newAddedSprite = _scrollingSprites.at((_end + 1) % _scrollingSprites.size())->getSprite();
        if (not newAddedSprite) { return; }
        
        // set position for the new commer
        _diffx = fabs(frontSprite->getPositionX()) - frontSprite->getContentSize().width * 0.5;
        newAddedSprite->setPositionX((_visibleSize.width * _scrollingWindowSize + (_visibleSize.width * 0.5)) - _diffx);

        // move the window of indexes which will be updated
        _start = (_start + 1) % _scrollingSprites.size();
        _end = _start + _scrollingWindowSize;
        
    }
    
}