#include "Chicken.h"
#include "Constants.h"

Chicken::Chicken(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Chicken::createChicken(cocos2d::Layer *layer) {
    _sprite = Sprite::create(_spriteImage);
    _sprite->setPosition(_visibleSize.width / 3 + _origin.x, _visibleSize.height / 2 + _origin.y);
    
    // adjusting big png
    auto scaleTo = ScaleTo::create(0.5f, 0.5f);
    _sprite->runAction(scaleTo);
    
    // flapping wings animation
//    Animation* animation = Animation::create();
//    animation->addSpriteFrameWithFile("playerfly_1.png");
//    animation->addSpriteFrameWithFile("playerfly_2.png");
//    animation->setDelayPerUnit(0.2f / 1.0f);
//    animation->setRestoreOriginalFrame(false);
//    animation->setLoops(-1);
//    
//    Action* action = Animate::create(animation);
//    _sprite->runAction(action);
    
    // physics body
    auto chickenBody = PhysicsBody::createCircle(_sprite->getContentSize().width / 2);
//    chickenBody->setDynamic(false);
    _sprite->setPhysicsBody(chickenBody);
    
    
    layer->addChild(_sprite, BackgroundLayer::layerChicken);
}
