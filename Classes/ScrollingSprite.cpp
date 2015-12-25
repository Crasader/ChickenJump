#include "ScrollingSprite.h"

using namespace cocos2d;

ScrollingSprite::ScrollingSprite(std::string const& imageFile, cocos2d::Layer* layer, BackgroundLayer const z, int const index) {
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    _sprite = Sprite::create(imageFile);
    if (_sprite) {
        _sprite->setPosition(_visibleSize.width * index + (_visibleSize.width * 0.5), _visibleSize.height * 0.5);
        layer->addChild(_sprite, z);
    }
}

Sprite* ScrollingSprite::getSprite() {
    return _sprite;
}

void ScrollingSprite::update(float speed) {
    if (not _sprite) { return; }

    _sprite->setPositionX(_sprite->getPositionX() - speed);
}
