#include "Chicken.h"

#include "Constants.h"

Chicken::Chicken(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Chicken::addPhysicsBody() {
    auto chickenBody = PhysicsBody::createCircle(_chicken->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    chickenBody->setCategoryBitmask(CATEGORY_BITMASK_CHICKEN);
    chickenBody->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_ALL);
    chickenBody->setCollisionBitmask(false); // not to get dragged-by others
    chickenBody->setGravityEnable(false);
    _chicken->setPhysicsBody(chickenBody);
}

void Chicken::applySpeedX(float speed) {
    _vector.x += speed;
    if (_vector.x <= 1) {
        _vector.x = 1; // minimum speed
    }
}

void Chicken::createChicken(cocos2d::Layer *layer) {
    if (not layer) { return; }

    _chicken = Sprite::create(_imageFile);
    
    if (! _chicken) { return; }
    
    _chicken->setAnchorPoint(Vec2(0, 0));
    
    // Dynamic physics body
    addPhysicsBody();
    
    // initial speed, weight and state
    _vector.x = 1.0;
    _vector.y = 0.0;
    _state = PlayerState::falling;
    _weight = 1.0;
    _scale = 1.0;
    
    // initial position
    _chicken->setPosition(_visibleSize.width * 0.30 + _origin.x, _visibleSize.height * 0.9 + _origin.y);
    
    // TODO: remove this adjusting
    // Adjusting big png
//    auto scaleTo = ScaleTo::create(0.75f, 0.75f);
//    _chicken->runAction(scaleTo);
    
    // Flapping wings animation
    setAnimation();
    
    layer->addChild(_chicken, BackgroundLayer::layerChicken);
}

void Chicken::decreaseSpriteSize() {
    if (_scale - SCALE_FACTOR <= MIN_SCALE) {
        auto scaleTo = ScaleTo::create(0.1f, _scale -= SCALE_FACTOR);
        _chicken->runAction(scaleTo);
        decreaseWeight();
    }
}

void Chicken::decreaseVectorX() {
    _vector.x /= ACCELERATION_DEFAULT;
    if (_vector.x <= 1) {
        _vector.x = 1;
    }
}

void Chicken::decreaseWeight() {
    if (_weight - SCALE_FACTOR <= MIN_WEIGHT) {
        _weight -= SCALE_FACTOR;
    }
}

PlayerState Chicken::getState() {
    if (not _chicken) { return PlayerState::start; }
    
    return _state;
}

float Chicken::getVectorX() {
    return _vector.x;
}

void Chicken::increaseSpriteSize() {
    if (_scale + SCALE_FACTOR <= MAX_SCALE) {
        auto scaleTo = ScaleTo::create(0.1f, _scale += SCALE_FACTOR);
        _chicken->runAction(scaleTo);
        increaseWeight();
    }
}

void Chicken::increaseVectorX() {
    if (_state == PlayerState::dying) { return; }
    
    _vector.x *= ACCELERATION_DEFAULT;   // increase speed by 1.5
    if (_vector.x >= MAX_SPEED_X) {
        _vector.x = MAX_SPEED_X;
    }
}

void Chicken::increaseWeight() {
    if (_weight + SCALE_FACTOR <= MAX_WEIGHT) {
        _weight += SCALE_FACTOR;
    }
    CCLOG("+++++ %f", _weight);
}

//void Chicken::moveToFinishingPosition() {
//    if (not _chicken) { return; }
//    
//    auto action = MoveTo::create(1, Point(_chicken->getPosition().x, _visibleSize.height * 0.60));
//    _chicken->runAction(action);
//}

//void Chicken::runFinishingMove() {
//    if (not _chicken) { return; }
//    
//    auto action = MoveTo::create(1, Point(_visibleSize.width + _chicken->getContentSize().width * 1.5, _visibleSize.height * 0.60));
//    _chicken->runAction(action);
//}

void Chicken::resetSizeAndWeight() {
    _scale = MIN_SCALE;
    _weight = MIN_WEIGHT;
    CCLOG("+++++ RESET %f", _weight);
}

void Chicken::setAnimation() {
    Animation* animation = Animation::create();
    animation->addSpriteFrameWithFile("playerfly_1.png");
    animation->addSpriteFrameWithFile("playerfly_2.png");
    animation->addSpriteFrameWithFile("playerfly_3.png");
    animation->setDelayPerUnit(0.2f / 1.0f);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(-1);
    
    Action* action = Animate::create(animation);
    _chicken->runAction(action);
}

void Chicken::setState(PlayerState state) {
    if (not _chicken) { return; }
    
    _state = state;
    if (state == PlayerState::jumping) {
        _vector.y = _visibleSize.height * VELOCITY_Y_MAX;
    }
    else if (state == PlayerState::falling) {
        _vector.y = -_visibleSize.height * VELOCITY_Y_DECREASE_RATE;
    }
}

void Chicken::update(float speed) {
    if (not _chicken) { return; }
    
    switch (_state) {
        case start:
            _vector.y = 0;
            break;
        case jumping:
            _vector.y -= _visibleSize.height * VELOCITY_Y_DECREASE_RATE * _weight;
            if (_vector.y <= 0) {
                _state = PlayerState::falling;
            }
            break;
        case falling:
            _vector.y -= _visibleSize.height * VELOCITY_Y_DECREASE_RATE * _weight;
            break;
        case dying:
            CCLOG("Player DEAD. PLEASE RESET");
            break;
        default:
            CCLOG("Program Should Not Hit This Point");
            break;
    }

    // jumping
    if (_state != PlayerState::dying) {
        _chicken->setPositionY(_chicken->getPositionY() + _vector.y);
    }
    
    // Die
    if (_chicken->getPositionY() < -_chicken->getContentSize().height * 0.5 or
        _chicken->getPositionX() < -_chicken->getContentSize().width * 1.5) {
        _state = PlayerState::dying;
    }
}










