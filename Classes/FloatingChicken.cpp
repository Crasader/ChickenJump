#include "FloatingChicken.h"

#include "Constants.h"

using namespace cocos2d;

FloatingChicken::FloatingChicken(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void FloatingChicken::createFloatingChicken(cocos2d::Layer *layer, Vec2 const& initialPosition, AnimationType const& animationType) {
    if (not layer) { return; }

    _chicken = Sprite::create(_imageFile);
    if (! _chicken) { return; }
    _chicken->setAnchorPoint(Vec2(0, 0));
    _initialPosition = initialPosition;
    gotoInitialPosition(_initialPosition);
    layer->addChild(_chicken, BackgroundLayer::layerBackground);

    // set speed into x axis, y axis is set and updated with FLYING_Y_DECREASE_RATE
    _vector = Vec2(3.5, 0.0);
    setState(FloatingChickenState::state_jumping);

    // set flying direction and flying height
    {
        switch (animationType) {
            case fly_lefttoright_high:
                _direction = 1;
                _parabolaHeight = 0.50;
                break;
            case fly_righttoleft_mid:
                _direction = 1;
                _parabolaHeight = 0.60;
                break;
            case fly_lefttoright_low:
                _direction = 1;
                _parabolaHeight = 0.70;
                break;
            case fly_lefttoright_mid:
                _direction = -1;
                _parabolaHeight = 0.60;
                break;
            default:
                break;
        }
    }

    setAnimation();
}

void FloatingChicken::gotoInitialPosition(Vec2 const& position) {
    _chicken->setPosition(position);
}

void FloatingChicken::setAnimation() {
    Animation* animation = Animation::create();
    if (_direction == 1) {
        animation->addSpriteFrameWithFile("playerfly_1.png");
        animation->addSpriteFrameWithFile("playerfly_2.png");
        animation->addSpriteFrameWithFile("playerfly_3.png");
        animation->setDelayPerUnit(0.2f / 1.0f);
        animation->setRestoreOriginalFrame(false);
        animation->setLoops(-1);

        Action* action = Animate::create(animation);
        _chicken->runAction(action);
    }
    else {
        animation->addSpriteFrameWithFile("playerfly_1_fliped.png");
        animation->addSpriteFrameWithFile("playerfly_2_fliped.png");
        animation->addSpriteFrameWithFile("playerfly_3_fliped.png");
        animation->setDelayPerUnit(0.2f / 1.0f);
        animation->setRestoreOriginalFrame(false);
        animation->setLoops(-1);

        Action* action = Animate::create(animation);
        _chicken->runAction(action);
    }
}

void FloatingChicken::setState(FloatingChickenState state) {
    if (not _chicken) { return; }

    _state = state;
    if (state == FloatingChickenState::state_jumping) {
        _vector.y = _visibleSize.height * FLYING_Y_MAX;
    }
    else if (state == FloatingChickenState::state_falling) {
        _vector.y = -_visibleSize.height * FLYING_Y_DECREASE_RATE;
    }
}

void FloatingChicken::update(float dt) {
    if (not _chicken) { return; }

    switch (_state) {
        case state_jumping:
            _vector.y -= _visibleSize.height * FLYING_Y_DECREASE_RATE * _parabolaHeight;
            if (_vector.y <= 0) {
                _state = FloatingChickenState::state_falling;
            }
            break;
        case state_falling:
            _vector.y -= _visibleSize.height * FLYING_Y_DECREASE_RATE * _parabolaHeight;
            break;
        default:
            // CCLOG("Program Should Not Hit This Point");
            break;
    }

    _chicken->setPosition(_chicken->getPositionX() + _vector.x * _direction, _chicken->getPositionY() + _vector.y);

    // Die and Re-born
    if (_chicken->getPositionY() < -_chicken->getContentSize().height or
        _chicken->getPositionX() > _visibleSize.width + _chicken->getContentSize().width) {

        // re-born
        auto callback = CallFunc::create([this]() {
            setState(FloatingChickenState::state_jumping);
            gotoInitialPosition(_initialPosition);
        } );

        Sequence* sequence = Sequence::create(DelayTime::create(1.5),
                                              callback,
                                              NULL);
        _chicken->runAction(sequence);
    }
}
