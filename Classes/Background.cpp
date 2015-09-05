#include "Background.h"

#include "Constants.h"

Background::Background(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Background::createBackground(cocos2d::Layer* layer) {
    
    _background = Sprite::create(_imageFile);
    _background->setAnchorPoint(Vec2(0,0));
    _background->setPosition(Point(0, _visibleSize.height / 2 - _background->getContentSize().height / 2));

    auto bg2 = Sprite::create(_imageFile);
    bg2->setAnchorPoint(Vec2(0,0));
    bg2->setPosition(Point(_background->getContentSize().width, 0));
    
    auto bg3 = Sprite::create(_imageFile);
    bg3->setAnchorPoint(Vec2(0,0));
    bg3->setPosition(Point(_background->getContentSize().width * 2, 0));

    _background->addChild(bg2);
    _background->addChild(bg3);
    
    layer->addChild(_background, BackgroundLayer::layerBackground);
}

void Background::update(float dt) {
    if (not _background) { return; }
    
    _background->setPositionX(_background->getPosition().x - std::abs(LAYER_ONE_SPEED * _visibleSize.width));
    
    float diffx;
    if (_background->getPositionX() < -_background->getContentSize().width) {
        diffx = fabs(_background->getPositionX()) - _background->getContentSize().width;
        _background->setPositionX(-diffx);
    }
}