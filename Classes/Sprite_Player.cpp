//
//  Sprite_Player.cpp
//  ChickenJump
//
//  Created by Asish Biswas on 16/05/15.
//
//

#include "Sprite_Player.h"

Player::Player(void){
    _screenSize = Director::getInstance()->getWinSize();
    _floatingTimerMax = 2;
    _floatingTimer = 0;
    _speed = PLAYER_INITIAL_SPEED;
    _maxSpeed = PLAYER_INITIAL_SPEED;
    _floating = false;
    _nextPosition = Vec2(0,0);
    _nextPosition.y = _screenSize.height * 0.6f;
    _state = kPlayerMoving;
    _jumping = false;
    _hasFloated = false;
}

Player::~Player(void){
}

Player * Player::create() {
    Player *player = new Player();
    
    if (player and player->initWithFile("player.png")) {
        player->autorelease();
        player->setSize();
        player->initPlayer();
        return player;
    }
    
    CC_SAFE_DELETE(player);
    return nullptr;
}

// Private function
void Player::initPlayer() {
    CCLOG("Player::initPlayer");
    this->setAnchorPoint(Vec2(0.5f, 1.0f));
    this->setPosition(Vec2(_screenSize.width * 0.2f, _nextPosition.y));
    _height = 252 * 0.95f;
    _width = 184;
    
//    Animation* animation;
//    animation = Animation::create();
//    SpriteFrame * frame;
//    int i;
//    for(i = 3; i >= 1; i--) {
//        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("player_%i.png", i)->getCString());
//        animation->addSpriteFrame(frame);
//    }
//    
//    animation->setDelayPerUnit(0.2f / 1.0f);
//    animation->setRestoreOriginalFrame(false);
//    animation->setLoops(-1);
//    _rideAnimation = Animate::create(animation);
//    _rideAnimation->retain();
//    
//    
//    auto easeSwing = Sequence::create(EaseInOut::create(RotateTo::create(0.8f, -10), 2),
//                                      EaseInOut::create(RotateTo::create(0.8f, 10), 2),
//                                      nullptr);
//    _floatAnimation = RepeatForever::create( (ActionInterval*) easeSwing );
//    _floatAnimation->retain();
//    
//    this->runAction(_rideAnimation);

//    CCLOG("Player::initPlayer::position %f, %f", this->getPositionX(), this->getPositionY());
//    CCLOG("Player::initPlayer::size %f, %f", this->getHeight(), this->getWidth());
}

void Player::reset() {
    _speed = PLAYER_INITIAL_SPEED;
    _maxSpeed = PLAYER_INITIAL_SPEED;
    _vector = Vec2(0,0);
//    this->setFloating(false);
    this->setRotation(0);
    _nextPosition.y = _screenSize.height * 0.6f;
    this->setPosition(Vec2( _screenSize.width * 0.2f, _nextPosition.y ));
    _state = kPlayerMoving;
    _jumping = false;
    _hasFloated = false;
}

void Player::setFloating (bool value) {
    if (_floating == value) return;
    
    if (value && _hasFloated) return;
    
    _floating = value;
    
    this->stopAllActions();
    
    if (value) {
        _hasFloated = true;
//        this->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player_float.png"));
//        this->runAction(_floatAnimation);
        _vector.y += PLAYER_JUMP * 0.5f;
    } else {        
//        this->runAction(_rideAnimation);
    }
}

void Player::update(float dt) {
    if(_speed + P_ACCELERATION <= _maxSpeed) {
        _speed += P_ACCELERATION;
    } else {
        _speed = _maxSpeed;
    }
    
    _vector.x = _speed;
    
    switch(_state) {
        case kPlayerMoving:
            _vector.y -= FORCE_GRAVITY;
            if (_hasFloated) _hasFloated = false;
            break;
            
        case kPlayerFalling:
            if (_floating ) {
                _vector.y -= FLOATNG_GRAVITY;
                _vector.x *= FLOATING_FRICTION;
                
            } else {
                _vector.y -= FORCE_GRAVITY;
                _vector.x *= AIR_FRICTION;
                _floatingTimer = 0;
            }
            break;
        case kPlayerDying:
            _vector.y -= FORCE_GRAVITY;
            _vector.x = -_speed;
            this->setPositionX(this->getPositionX() + _vector.x);
            break;
    }
    
    if(_jumping) {
        _state = kPlayerFalling;
        _vector.y += PLAYER_JUMP * 0.25f;
        if (_vector.y > PLAYER_JUMP ) _jumping = false;
    }
    
    if(_vector.y < -TERMINAL_VELOCITY) _vector.y = -TERMINAL_VELOCITY;
    
    _nextPosition.y = this->getPositionY() + _vector.y;
    
    if (_vector.x * _vector.x < 0.01) _vector.x = 0;
    if (_vector.y * _vector.y < 0.01) _vector.y = 0;
    
    if(_floating) {
        _floatingTimer += dt;
        if (_floatingTimer > _floatingTimerMax) {
            _floatingTimer = 0;
//            this->setFloating(false);
        }
    }
}

