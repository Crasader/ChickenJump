#include "Trampoline.h"

#include "Constants.h"

Trampoline::Trampoline(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    _trampoline = Sprite::create();     // Think it as the HEAD of a Linked List
    _isDrawingFinished = false;
    _spriteToKnowContentWidth = Sprite::create(_imageFile);
    _trampolineWidth = _spriteToKnowContentWidth->getContentSize().width;

}

Sprite* Trampoline::getTrampoline() const {
    return _trampoline;
}

void Trampoline::createTrampoline(cocos2d::Layer* layer, Vec2 lineStartPoint, Vec2 lineEndPoint) {
    
    _trampoline->setPosition(Vec2(lineStartPoint.x, lineStartPoint.y));
    _trampoline->setAnchorPoint(Vec2(0, 0));
    
    float xDist = (lineEndPoint.x - lineStartPoint.x);
    float yDist = (lineEndPoint.y - lineStartPoint.y);
    float distance = lineEndPoint.distance(lineStartPoint); // distance = √(x^2 + y^2)
    
    float degree = atan2(yDist, xDist) * 180 / PI;
    
    // Restrict to max trampoline size
    if (distance > _visibleSize.width / 3) {
        distance = _visibleSize.width / 3;
        
        lineEndPoint = lineStartPoint + Vec2(cos(degree2radian(degree)) * distance,
                                             sin(degree2radian(degree)) * distance);
        xDist = (lineEndPoint.x - lineStartPoint.x);
        yDist = (lineEndPoint.y - lineStartPoint.y);
    }
        
    int numberOfSpritesNeeded = distance / _trampolineWidth - 1;
    
    for (int i = 0; i < numberOfSpritesNeeded; ++i) {        
        auto sprite = Sprite::create(_imageFile);
        sprite->setPosition( Vec2((i * (xDist/numberOfSpritesNeeded)),
                                  (i * (yDist/numberOfSpritesNeeded))) );
        
        sprite->setAnchorPoint(Vec2(0, 0));
        
        // create a static PhysicsBody and set it to the sprite
        auto physicsBody = PhysicsBody::createCircle(_trampolineWidth / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicsBody->setCollisionBitmask(COLLISION_BITMASK_OBSTACLE);
        physicsBody->setContactTestBitmask(true);
        physicsBody->setDynamic(false);
        sprite->setPhysicsBody(physicsBody);
        
        _trampoline->addChild(sprite, BackgroundLayer::layerChicken);

    }
    
    layer->addChild(_trampoline, BackgroundLayer::layerChicken);
}

void Trampoline::update(float dt) {
    if (_isDrawingFinished and _trampoline) {
        _trampoline->setPositionX(_trampoline->getPosition().x - std::abs(LAYER_GROUND_SPEED * _visibleSize.width));
    }
}















