#ifndef __CHICKEN_SPRITE__
#define __CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum
{
    Moving,
    Jumping,
    Falling,
    Dying
    
} PlayerState;


class Chicken {
public:
    Chicken(void);
    void createChicken(cocos2d::Layer* layer);
    Sprite* getSprite() { return _sprite; }
    void setState(PlayerState state);
    inline void setVectorX(int x) { _vector.x = x; }
    inline void setVectorY(int y) { _vector.y = y; }
    void update(float dt);

private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _sprite;
    PlayerState _state;
    Point _vector;
    
    std::string const _imageFile = "playerfly_1.png";
};



#endif /* __CHICKEN_SPRITE__ */
