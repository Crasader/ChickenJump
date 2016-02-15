#ifndef __FLOATING_CHICKEN_SPRITE__
#define __FLOATING_CHICKEN_SPRITE__

#include <cocos2d.h>

typedef enum { fly_lefttoright_high, fly_lefttoright_mid, fly_lefttoright_low, fly_righttoleft_mid } AnimationType;
typedef enum { state_jumping, state_falling } FloatingChickenState;

/* This class is for HomeLayer's Floating Chicken */
class FloatingChicken {
public:
    FloatingChicken(void);
    void createFloatingChicken(cocos2d::Layer* layer, cocos2d::Vec2 const& initialPosition, AnimationType const& animationType); // direction = left->right OR right->left
    
    void gotoInitialPosition(cocos2d::Vec2 const& position);
    cocos2d::Sprite* getFloatingChicken() { return _chicken; }
    cocos2d::Vec2 getPosition() { return _chicken->getPosition(); }
    void setPosition(cocos2d::Vec2 const& position) { _chicken->setPosition(position); }
    void setState(FloatingChickenState state);
    
    void update(float dt);
private:
    void setAnimation();

    cocos2d::Sprite* _chicken;
    cocos2d::Vec2 _vector;
    cocos2d::Vec2 _initialPosition;
    int _direction; // direction = +ve: left->right OR -ve: right->left
    float _parabolaHeight = 1.0;
    FloatingChickenState _state;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;

    std::string const _imageFile = "playerfly_1.png";
};



#endif /* __FLOATING_CHICKEN_SPRITE__ */
