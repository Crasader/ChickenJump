#include "Trampoline.h"

#include "Constants.h"

using namespace cocos2d;

bool Trampoline::isDrawingOngoing = false;

Trampoline::Trampoline(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    _trampoline = Sprite::create();     // Think it as the HEAD of a Linked List
    _spriteToKnowContentWidth = Sprite::create(_imageFile);
    if (_spriteToKnowContentWidth) { _trampolineWidth = _spriteToKnowContentWidth->getContentSize().width; }

}

Sprite* Trampoline::getTrampoline() const {
    return _trampoline;
}

void Trampoline::createTrampoline(cocos2d::Layer* layer, Vec2 lineStartPoint, Vec2 lineEndPoint) {
    if (not layer) { return; }

    _trampoline->setAnchorPoint(Vec2(0, 0));
    _trampoline->setPosition(Vec2(lineStartPoint.x, lineStartPoint.y - layer->getPositionY()));
    
    float xDist = (lineEndPoint.x - lineStartPoint.x);
    float yDist = (lineEndPoint.y - lineStartPoint.y);
    float distance = lineEndPoint.distance(lineStartPoint); // distance = √(x^2 + y^2)
    
    float degree = atan2(yDist, xDist) * 180 / PI;
    
    /* Trampoline drawing is finished once we reach the max length of trampoline.
     * Restrict to max trampoline size and
     * Finish trampoline drawing and enable update method to move the trampoline */
    if (distance > _visibleSize.width * 0.25) {
        distance = _visibleSize.width * 0.25;
        isDrawingOngoing = false;
        
        lineEndPoint = lineStartPoint + Vec2(cos(degree2radian(degree)) * distance,
                                             sin(degree2radian(degree)) * distance);
        xDist = (lineEndPoint.x - lineStartPoint.x);
        yDist = (lineEndPoint.y - lineStartPoint.y);
    }
        
    int numberOfSpritesNeeded = distance / _trampolineWidth;
    
    for (int i = 0; i < numberOfSpritesNeeded; ++i) {        
        auto sprite = Sprite::create(_imageFile);
        sprite->setPosition( Vec2((i * (xDist/numberOfSpritesNeeded)),
                                  (i * (yDist/numberOfSpritesNeeded))) );
        
        sprite->setAnchorPoint(Vec2(0, 0));
        
        // create a static PhysicsBody and set it to the sprite
        auto physicsBody = PhysicsBody::createCircle(_trampolineWidth / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicsBody->setCategoryBitmask(CATEGORY_BITMASK_TRAMPOLINE);
        // physicsBody->setCollisionBitmask(1);
        physicsBody->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
        physicsBody->setDynamic(false);
        sprite->setPhysicsBody(physicsBody);
        
        _trampoline->addChild(sprite, BackgroundLayer::layerChicken);

    }
    
    layer->addChild(_trampoline, BackgroundLayer::layerGround);
}

void Trampoline::update(float speed) {
    // when trampoline drawing is done, start to move trampoline according to chicken's speedX
    if (_trampoline and not isDrawingOngoing) {
        _trampoline->setPositionX(_trampoline->getPosition().x - LAYER_GROUND_SPEED * _visibleSize.width * speed);
    }
}
















