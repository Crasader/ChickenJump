#ifndef __FLOATING_CHICKEN_SPRITE__
#define __FLOATING_CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum { high, mid, flat } ParabolaSize;
typedef enum { jumping, falling } FloatingChickenState;

/* This class is for HomeLayer's Floating Chicken */
class FloatingChicken {
public:
    FloatingChicken(void);
    void createFloatingChicken(cocos2d::Layer* layer, Vec2 initialPosition, int direction, ParabolaSize parabolaSize); // direction = left->right OR right->left
    
    void gotoInitialPosition(Vec2 position);
    Sprite* getFloatingChicken() { return _chicken; }
    Vec2 getPosition() { return _chicken->getPosition(); }
    void setPosition(Vec2 const& position) { _chicken->setPosition(position); }
    void setState(FloatingChickenState state);
//    void setAnimationPositions();
    
    void update(float dt);
private:
    void setAnimation();

    Sprite* _chicken;
    Vec2 _vector;
    Vec2 _initialPosition;
    int _direction; // direction = +ve: left->right OR -ve: right->left
    float _parabolaHeight = 1.0;
    FloatingChickenState _state;
    
    Vec2 _origin;
    Size _visibleSize;

    std::string const _imageFile = "playerfly_1.png";
};



#endif /* __FLOATING_CHICKEN_SPRITE__ */
