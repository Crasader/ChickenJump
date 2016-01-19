#include "ScrollingLayerBase.h"

#include "Constants.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;

ScrollingLayerBase::ScrollingLayerBase(void) : _scrollingWindowSize(2), _scrolled(0), _diffx(0), _currentLayerImageIndex(0) {
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _root = Sprite::create("blank.png");
    if (not _root) { return; }
    _root->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    
    _checkpoint = _visibleSize.width * 0.5;
}

ScrollingLayerBase::~ScrollingLayerBase() {

}

void ScrollingLayerBase::createLayer(cocos2d::Layer *layer) {
    if (not layer) { return; }

    // Use 3 images to implement scrolling (use 6 for infinite stage)
    int numberOfScrollingSprite = _stage.getName() == StageStatus::infinite ? 6 : 3;
    
    _scrollingWindowSize = numberOfScrollingSprite - 1; // 0 based index
    
    for (int i = 0; i < numberOfScrollingSprite; ++i) {
        Sprite* ss = Sprite::create(_scrollingImages.at(_currentLayerImageIndex % _scrollingImages.size()));//, _root, _zOrder, i);
        ++_currentLayerImageIndex;
        
        if (not ss) { return; }
        ss->setAnchorPoint(Vec2(0, 0));
        ss->setPosition(i * ss->getContentSize().width - ss->getContentSize().width * 0.5,
                        -ss->getContentSize().height * 0.5);
        
        ss->setTag(i);
        _root->addChild(ss);
        
        _scrollingSprites.push(ss);
    }
    
    layer->addChild(_root, _zOrder);
}

void ScrollingLayerBase::update(float speed) {
    if (_scrollingSprites.empty()) { return; }
    
    // scroll like pulling a rope
    _root->setPositionX(_root->getPositionX() - speed);
    _scrolled = (_visibleSize.width * 0.5) - _root->getPositionX();
    
    // since our _root is in the middle of the _visibleSize and scrollingSprite's ancorpoint is 0,0
    // we need to scroll 1.5 image width to the left
    if (_checkpoint - _root->getPositionX() > _visibleSize.width) {
        _checkpoint = _checkpoint - _visibleSize.width;
        _diffx = _checkpoint - _root->getPositionX();

        _root->removeChild(_scrollingSprites.front(), true);
        _scrollingSprites.pop();
        
        _newSprite = Sprite::create(_scrollingImages.at(_currentLayerImageIndex % _scrollingImages.size()));
        ++_currentLayerImageIndex;
        if (not _newSprite) { return; }
        
        _newSprite->setAnchorPoint(Vec2(0, 0));
        // _newSprite should go at the 4th position (respecting _root's position and _diffx).
        // 1st image has passed, 2nd is visible now, 3rd is coming, then comes new(4th)...for infinite stage it goes up until 7th
        _newSprite->setPosition(_scrolled + (_scrollingWindowSize * _visibleSize.width - _visibleSize.width * 0.5) - _diffx,
                                -_newSprite->getContentSize().height * 0.5);
        
        _root->addChild(_newSprite);
        _scrollingSprites.push(_newSprite);
    }

}

