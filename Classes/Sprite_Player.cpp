//
//  Sprite_Player.cpp
//  ChickenJump
//
//  Created by Asish Biswas on 16/05/15.
//
//

#include "Sprite_Player.h"

#define ACCELERATION 0.5
#define AIR_FRICTION 0.99f
#define FLOATING_FRICTION 0.98f
#define FLOATNG_GRAVITY 0.4
#define GRAVITY 1.5
#define PLAYER_JUMP 42
#define TERMINAL_VELOCITY 70

Player::Player(void){
}

Player::~Player(void){
}

Player * Player::create() {
    Player * player = new Player();
    if (player && player->initWithFile("spaceship.png")) {
        CCLOG("Player::create");
        player->autorelease();
//        player->setSize();
        player->initPlayer();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

// Private function
void Player::initPlayer() {
    CCLOG("Player::initPlayer");
    this->setAnchorPoint(Point(0.5f, 1.0f));
    this->setPosition(Point(100, 100));
    
    _height = 228;
    _width = 180;
    this->setTextureRect(Rect(0, 0, _width, _height));
    this->setColor(Color3B(255,255,255));
    CCLOG("Player::initPlayer::position %f, %f", this->getPositionX(), this->getPositionY());
    CCLOG("Player::initPlayer::size %f, %f", this->getHeight(), this->getWidth());
}

//void Player::reset() {
//    _speed = PLAYER_INITIAL_SPEED;
//    _maxSpeed = PLAYER_INITIAL_SPEED;
//    _vector = Vec2(0,0);
//    this->setFloating(false);
//    this->setRotation(0);
//    _nextPosition.y = _screenSize.height * 0.6f;
//    this->setPosition(Vec2( _screenSize.width * 0.2f, _nextPosition.y ));
//    _state = kPlayerMoving;
//    _jumping = false;
//    _hasFloated = false;
//}

//void Player::setFloating (bool value) {
//    if (_floating == value) return;
//    
//    if (value && _hasFloated) return;
//    
//    _floating = value;
//    
//    if (value) {
//        _hasFloated = true;
//        _vector.y += PLAYER_JUMP * 0.5f;
//    }
//}

//void Player::update(float dt) {
//    if (_speed + ACCELERATION <= _maxSpeed) {
//        _speed += ACCELERATION;
//    } else {
//        _speed = _maxSpeed;
//    }
//    
//    _vector.x = _speed;
//    
//    switch (_state) {
//        case kPlayerMoving:
//            _vector.y -= GRAVITY;
//            if (_hasFloated) _hasFloated = false;
//            break;
//            
//        case kPlayerFalling:
//            
//            if (_floating ) {
//                _vector.y -= FLOATNG_GRAVITY;
//                _vector.x *= FLOATING_FRICTION;
//                
//            } else {
//                _vector.y -= GRAVITY;
//                _vector.x *= AIR_FRICTION;
//                _floatingTimer = 0;
//            }
//            break;
//        case kPlayerDying:
//            _vector.y -= GRAVITY;
//            _vector.x = -_speed;
//            this->setPositionX(this->getPositionX() + _vector.x);
//            break;
//            
//    }
//    
//    if (_jumping) {
//        _state = kPlayerFalling;
//        _vector.y += PLAYER_JUMP * 0.25f;
//        if (_vector.y > PLAYER_JUMP ) _jumping = false;
//    }
//    
//    if (_vector.y < -TERMINAL_VELOCITY) _vector.y = -TERMINAL_VELOCITY;
//    
//    _nextPosition.y = this->getPositionY() + _vector.y;
//    
//    if (_floating) {
//        _floatingTimer += dt;
//        if (_floatingTimer > _floatingTimerMax) {
//            _floatingTimer = 0;
//            this->setFloating(false);
//        }
//    }
//}

