#include "LayerGround.h"

#include "Constants.h"

LayerGround::LayerGround(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void LayerGround::createLayerGround(cocos2d::Layer* layer) {

    _layerGround = Sprite::create(_imageFile);
    _layerGround->setAnchorPoint(Vec2(0,0));
    _layerGround->setPosition(Point(0, _visibleSize.height / 2 - _layerGround->getContentSize().height / 2));

    auto bg2 = Sprite::create(_imageFile);
    bg2->setAnchorPoint(Vec2(0,0));
    bg2->setPosition(Point(_layerGround->getContentSize().width, 0));
    
    auto bg3 = Sprite::create(_imageFile);
    bg3->setAnchorPoint(Vec2(0,0));
    bg3->setPosition(Point(_layerGround->getContentSize().width * 2, 0));

    _layerGround->addChild(bg2);
    _layerGround->addChild(bg3);
    
    layer->addChild(_layerGround, BackgroundLayer::layerGround);
}

void LayerGround::update(float dt) {
    _layerGround->setPositionX(_layerGround->getPosition().x - std::abs(LAYER_GROUND_SPEED * _visibleSize.width));
    
    float diffx;
    if (_layerGround->getPositionX() < -_layerGround->getContentSize().width) {
        diffx = fabs(_layerGround->getPositionX()) - _layerGround->getContentSize().width;
        _layerGround->setPositionX(-diffx);
    }
}