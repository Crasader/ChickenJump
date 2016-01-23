#ifndef __CHICKEN_SPRITE__
#define __CHICKEN_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum
{
    start,
    newBorn,
    invisible,
    jumping,
    falling,
    dying

} PlayerState;


class Chicken {
public:
    Chicken(void);
    void addPhysicsBody();
    void applySpeedX(float speed);
    void createChicken(cocos2d::Layer* layer);
    void decreaseLife();
    void decreaseSpriteSize();
    void decreaseVectorX();
    Sprite* getChicken() { return _chicken; }
    int getLives() { return _lives; }
    Vec2 getPosition() { return _chicken->getPosition(); }
    PlayerState getState();
    float getVectorX();
    Vec2* getVector() { return &_vector; }
    void increaseLife();
    void increaseSpriteSize();
    void resetSizeAndWeight();
    void setAnimation();
    void setCollideToAll();
    void setCollideToNoBomb();
    void setCollideToNone();
    void setLives(int numberOfLives);
    void setState(PlayerState state);
    void setVector(Vec2 vector) { _vector = vector; }
    void update(float dt);

private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _chicken;
    PlayerState _state;
    Vec2 _vector;
    float _weight;
    float _scale;
    
    unsigned int _lives;
    
    void decreaseWeight();
    void increaseWeight();
    
    std::string const _imageFile = "playerfly_1.png";
};



#endif /* __CHICKEN_SPRITE__ */
