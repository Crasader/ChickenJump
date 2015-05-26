//
//  Sprite_Player.h
//  ChickenJump
//
//  Created by Asish Biswas on 16/05/15.
//
//

#ifndef SPRITE_PLATER
#define SPRITE_PLATER

#include <cocos2d.h>

#define PLAYER_INITIAL_SPEED 8
#define PLAYER_JUMP 42
#define FORCE_GRAVITY 1.5
#define FLOATNG_GRAVITY 0.4
#define TERMINAL_VELOCITY 70
#define FLOATING_FRICTION 0.98f
#define AIR_FRICTION 0.99f

using namespace cocos2d;

typedef enum
{
    kPlayerMoving,
    kPlayerFalling,
    kPlayerDying
    
} PlayerState;


class Player : public Sprite {
public:
    // GameSprites 4 basic attributes
    CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(Point, _vector, Vector);
    
    CC_SYNTHESIZE(PlayerState, _state, State);
    CC_SYNTHESIZE(bool, _inAir, InAir);
    CC_SYNTHESIZE_READONLY(bool, _floating, Floating);
    CC_SYNTHESIZE(bool, _jumping, Jumping);
    CC_SYNTHESIZE(float, _maxSpeed, MaxSpeed);
    
    
    Player(void);
    ~Player(void);
    
    // Create our Player sprite
    static Player * create(void);
    void reset(void);
    void setFloating(bool value);
    
    // Set Player position
    inline virtual void setPosition(const Point& pos) override {
        Sprite::setPosition(pos);
    }
    
//    inline void place() {
//        this->setPositionY( _nextPosition.y );
//        if (_vector.x > 0 && this->getPositionX() < _screenSize.width * 0.2f) {
//            this->setPositionX(this->getPositionX() + _vector.x);
//            if (this->getPositionX() > _screenSize.width * 0.2f) {
//                this->setPositionX(_screenSize.width * 0.2f);
//            }
//        }
//    }
    
//    inline void setSize() {
//        _width = this->getBoundingBox().size.width;
//        _height = this->getBoundingBox().size.height;
//    }
    
//    virtual void update(float dt);
    
    // get coordinates
    inline int left() {
        return this->getPositionX() - _width * 0.5f;
    }
    
    inline int right() {
        return this->getPositionX() + _width * 0.5f;
    }
    
    inline int top() {
        return this->getPositionY() ;
    }
    
    inline int bottom() {
        return this->getPositionY() - _height ;
    }
    
    // for colission detection
    inline int next_left() {
        return _nextPosition.x - _width * 0.5f;
    }
    
    inline int next_right() {
        return _nextPosition.x + _width * 0.5f;
    }
    
    inline int next_top() {
        return _nextPosition.y ;
    }
    
    inline int next_bottom() {
        return _nextPosition.y - _height;
    }
    
private:
    
    float _speed;
    
    int _floatingTimerMax;
    float _floatingTimer;
    int _floatingInterval;
    bool _hasFloated;
    
//    Size _screenSize;
    
    // Private functions
    void initPlayer (void);
};



#endif /* defined(SPRITE_PLATER) */
