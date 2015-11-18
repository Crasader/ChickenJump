#include "Chicken.h"

Chicken::Chicken(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Chicken::createChicken(cocos2d::Layer *layer) {
    _sprite = Sprite::create(_spriteImage);
    layer->addChild(_sprite);
}
