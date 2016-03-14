#include "Chicken.h"

#include "Constants.h"
#include "SoundManager.h"

static const std::string soundDead = "dead.wav";

Chicken::Chicken(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _chicken = nullptr;
    _scaleUp = nullptr;
    _scaleDown = nullptr;
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

    // Bound Max & Min Speed
    if (_vector.x + speed >= MIN_SPEED_X and _vector.x + speed <= MAX_SPEED_X) {
        _vector.x += speed;
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
    _hasMagnetEffect = false;
    _isInvisible = false;
    
    // initial position
    _chicken->setPosition(_visibleSize.width * 0.30, _visibleSize.height * 0.9);
    
    // Flapping wings animation
    setDefaultAnimation();
    
    layer->addChild(_chicken, BackgroundLayer::layerChicken);
}

void Chicken::decreaseLife() {
    if (_state == PlayerState::dying) { return; }

    --_lives;
    resetSizeAndWeight();
}

void Chicken::decreaseSize() {
    if (_scale - SCALE_FACTOR >= MIN_SCALE) {
        
        if (_scaleDown) { _chicken->stopAction(_scaleDown); }
        
        _scaleDown = ScaleTo::create(0.1f, _scale -= SCALE_FACTOR);
        _chicken->runAction(_scaleDown);
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
    if (_weight - SCALE_FACTOR >= MIN_WEIGHT) {
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

bool Chicken::hasMagnetEffect() {
    return _hasMagnetEffect;
}

void Chicken::increaseLife() {
    if (_state == PlayerState::dying) { return; }
    if (_lives +1 <= CHICKEN_LIVES_MAX) {
        ++_lives;
    }
}

void Chicken::increaseSize() {
    if (_scale + SCALE_FACTOR <= MAX_SCALE) {
        if (_scaleUp) { _chicken->stopAction(_scaleUp); }
        
        _scaleUp = ScaleTo::create(0.1f, _scale += SCALE_FACTOR);
        _chicken->runAction(_scaleUp);
        increaseWeight();
    }
}

void Chicken::increaseWeight() {
    if (_weight + SCALE_FACTOR <= MAX_WEIGHT) {
        _weight += SCALE_FACTOR;
    }
}

void Chicken::makeInvisible() {
    _isInvisible = true;
    setInvisibilityAnimation();
}

void Chicken::makeVisible() {
    _isInvisible = false;
    setDefaultAnimation();
}

void Chicken::resetSizeAndWeight() {
    _scale = MIN_SCALE;
    _weight = MIN_WEIGHT;
    
    if (_scaleUp) { _chicken->stopAction(_scaleUp); }
    if (_scaleDown) { _chicken->stopAction(_scaleDown); }
    
    _scaleDown = ScaleTo::create(0.1f, _scale);
    _chicken->runAction(_scaleDown);
}

void Chicken::setDefaultAnimation() {
    if (not _chicken) { return; }
    
    _chicken->stopAllActions();
    
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

void Chicken::setInvisibilityAnimation() {
    if (not _chicken) { return; }
    
    _chicken->stopAllActions();
    
    Animation* animation = Animation::create();
    animation->addSpriteFrameWithFile("playerfly_1_invisible.png");
    animation->addSpriteFrameWithFile("playerfly_2_invisible.png");
    animation->addSpriteFrameWithFile("playerfly_3_invisible.png");
    animation->setDelayPerUnit(0.2f / 1.0f);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(-1);
    
    Action* action = Animate::create(animation);
    _chicken->runAction(action);
}

void Chicken::setCollideToAll() {
    if (not _chicken) { return; }
    _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_ALL);
}

void Chicken::setCollideToNoBomb(){
    if (not _chicken) { return; }
    _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_NO_BOMB);
}

void Chicken::setCollideToNone() {
    if (not _chicken) { return; }
    _chicken->getPhysicsBody()->setContactTestBitmask(CONTACTTEST_BITMASK_CHICKEN_NON);
}

void Chicken::setLives(int numberOfLives) {
    if (_state == PlayerState::dying) { return; }

    _lives = numberOfLives;
}

void Chicken::setMagnetEffect(bool magnetEffect) {
    _hasMagnetEffect = magnetEffect;
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
            
            auto resetChicken = CallFunc::create([this](){
                // reset size & weight; move to a stable position; remove collide power
                resetSizeAndWeight();
                _chicken->setPosition(_visibleSize.width * 0.30, _visibleSize.height * 0.60);
            });
            
            auto collideNone = CallFunc::create([this]() {
                setCollideToNone();
            });
            
            auto showChicken = CallFunc::create([this](){
                _chicken->setVisible(true);
            });

            auto hideChicken = CallFunc::create([this](){
                _chicken->setVisible(false);
            });

            auto stateFalling = CallFunc::create([this](){
                _state = PlayerState::falling;
                _vector = Vec2(1, 0); // set minimal speed after reborn
            });
            
            auto collideNoBomb = CallFunc::create([this]() {
                // get the collide power back
                setCollideToNoBomb();
            });

            auto collideAll = CallFunc::create([this]() {
                // get the collide power back
                setCollideToAll();
            });
            
            auto timeToReborn = DelayTime::create(2.0);
            auto delay = DelayTime::create(0.2);

            Sequence* blink = Sequence::create(timeToReborn, resetChicken, collideNone,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               stateFalling, collideNoBomb,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               hideChicken, delay, showChicken, delay,
                                               collideAll, NULL);
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
        
        SoundManager::Play(SoundManager::soundDead);
    }
}










