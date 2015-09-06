#ifndef __CHICKEN_SPRITE__
#define __CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum
{
    Dying,
    Falling,
    Jumping,
    Moving,
    Start
    
} PlayerState;


class Chicken {
public:
    Chicken(void);
    void createChicken(cocos2d::Layer* layer);
    Sprite* getChicken() { return _chicken; }
    float getSpeedX();
    void increaseSpeedX();
    void decreaseSpeedX();
    void setState(PlayerState state);
    PlayerState getState();
    inline void setVectorX(int x) { _vector.x = x; }
    inline void setVectorY(int y) { _vector.y = y; }
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
