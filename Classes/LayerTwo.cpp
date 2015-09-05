#include "LayerTwo.h"

#include "Constants.h"

LayerTwo::LayerTwo(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void LayerTwo::createLayerTwo(cocos2d::Layer* layer) {

    _layerTow = Sprite::create(_imageFile);
    _layerTow->setAnchorPoint(Vec2(0,0));
    _layerTow->setPosition(Point(0, _visibleSize.height / 2 - _layerTow->getContentSize().height / 2));

    auto bg2 = Sprite::create(_imageFile);
    bg2->setAnchorPoint(Vec2(0,0));
    bg2->setPosition(Point(_layerTow->getContentSize().width, 0));
    
    auto bg3 = Sprite::create(_imageFile);
    bg3->setAnchorPoint(Vec2(0,0));
    bg3->setPosition(Point(_layerTow->getContentSize().width * 2, 0));

    _layerTow->addChild(bg2);
    _layerTow->addChild(bg3);
    
    layer->addChild(_layerTow, BackgroundLayer::layerTwo);
}

void LayerTwo::update(float playerSpeed) {
    if (not _layerTow) { return; }
    
    _layerTow->setPositionX(_layerTow->getPosition().x - LAYER_TWO_SPEED * _visibleSize.width * playerSpeed);
    
    float diffx;
    if (_layerTow->getPositionX() < -_layerTow->getContentSize().width) {
        diffx = fabs(_layerTow->getPositionX()) - _layerTow->getContentSize().width;
        _layerTow->setPositionX(-diffx);
    }
}