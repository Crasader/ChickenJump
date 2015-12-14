#include "Chicken.h"

#include "Constants.h"
#include "SimpleAudioEngine.h"

static const std::string soundDead = "dead.wav";

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
    if (_state == PlayerState::dying) { return; }

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
    _scale = 1.0;
    _weight = 1.0;
    _vector = Vec2(1.0, 0.0);
    setState(PlayerState::falling);
    
    // initial position
    _chicken->setPosition(_visibleSize.width * 0.30, _visibleSize.height * 0.9);
    
    // Flapping wings animation
    setAnimation();
    
    layer->addChild(_chicken, BackgroundLayer::layerChicken);
}

void Chicken::decreaseLife() {
    if (_state == PlayerState::dying) { return; }

    --_lives;
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

void Chicken::increaseLife() {
    if (_state == PlayerState::dying) { return; }
    if (_lives +1 <= CHICKEN_LIVES_MAX) {
        ++_lives;
    }
}

void Chicken::increaseSpriteSize() {
    if (_scale + SCALE_FACTOR <= MAX_SCALE) {
        auto scaleTo = ScaleTo::create(0.1f, _scale += SCALE_FACTOR);
        _chicken->runAction(scaleTo);
        increaseWeight();
    }
}

void Chicken::increaseWeight() {
    if (_weight + SCALE_FACTOR <= MAX_WEIGHT) {
        _weight += SCALE_FACTOR;
    }
}

void Chicken::resetSizeAndWeight() {
    _scale = MIN_SCALE;
    _weight = MIN_WEIGHT;
}

void Chicken::setAnimation() {
    if (not _chicken) { return; }
    
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

void Chicken::setLives(int numberOfLives) {
    if (_state == PlayerState::dying) { return; }

    _lives = numberOfLives;
}


void Chicken::setState(PlayerState state) {
    if (not _chicken) { return; }
    
    _state = state;
    switch (_state) {
        case start:
            _vector = Vec2(0, 0);
            break;
        case newBorn: {
            // stop falling down, stop scrolling as well.
            _vector = Vec2(0, 0);
            
            auto callbackResetChicken = CallFunc::create([this](){
                // reset size & weight; move to a stable position; remove collide power
                resetSizeAndWeight();
                _chicken->setPosition(_visibleSize.width * 0.30, _visibleSize.height * 0.60);
            });
            
            auto callbackCollideNone = CallFunc::create([this]() {
                _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_NON);
            });
            
            auto callbackShowChicken = CallFunc::create([this](){
                _chicken->setVisible(true);
            });

            auto callbackHideChicken = CallFunc::create([this](){
                _chicken->setVisible(false);
            });

            auto callbackStateFalling = CallFunc::create([this](){
                _state = PlayerState::falling;
            });
            
            auto callbackCollideNoBomb = CallFunc::create([this]() {
                // get the collide power back
                _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_NO_BOMB);
            });

            auto callbackCollideAll = CallFunc::create([this]() {
                // get the collide power back
                _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_ALL);
            });
            
            auto timeToReborn = DelayTime::create(2.0);
            auto delay = DelayTime::create(0.2);

            Sequence* blink = Sequence::create(timeToReborn, callbackResetChicken, callbackCollideNone,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackStateFalling, callbackCollideNoBomb,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackHideChicken, delay, callbackShowChicken, delay,
                                               callbackCollideAll, NULL);
            _chicken->runAction(blink);
            break;
        }
        case jumping:
            _vector.y = _visibleSize.height * VELOCITY_Y_MAX;
            break;
        case falling:
            _vector.y = -_visibleSize.height * VELOCITY_Y_DECREASE_RATE;
            break;
        case dying:
            break;
    }
}

void Chicken::update(float speed) {
    if (not _chicken) { return; }
    if (_state == PlayerState::dying) { return; }
    
    switch (_state) {
        case start:
            break;
        case newBorn:
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

    // already in jumping state. no need to check if (_state != PlayerState::dying)
    _chicken->setPosition(Vec2(_chicken->getPositionX(), _chicken->getPositionY() + _vector.y));
    
    // Die
    if (_chicken->getPositionY() < -_chicken->getContentSize().height * 0.5 or
        _chicken->getPositionX() < -_chicken->getContentSize().width * 1.5) {
        _state = PlayerState::dying;
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundDead.c_str());
    }
}










