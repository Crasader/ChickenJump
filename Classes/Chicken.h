#ifndef __CHICKEN_SPRITE__
#define __CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum
{
    Dying,
    Falling,
    Jumping,
    Start
    
} PlayerState;


class Chicken {
public:
    Chicken(void);
    void addPhysicsBody();
    void createChicken(cocos2d::Layer* layer);
    void decreaseVectorX();
    Vec2 getPosition() { return _chicken->getPosition(); }
    PlayerState getState();
    float getVectorX();
    Vec2* getVector() { return &_vector; }
    void increaseVectorX();
    void setAnimation();
    void setState(PlayerState state);
    void setVectorX(float speed);
    void update(float dt);

private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _chicken;
    PlayerState _state;
    Vec2 _vector;
    
    std::string const _imageFile = "playerfly_1.png";
};



#endif /* __CHICKEN_SPRITE__ */
