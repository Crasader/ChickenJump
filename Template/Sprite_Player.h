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

using namespace cocos2d;

class Player : public Sprite {
public:
    Player(void);
    ~Player(void);
    
    static Player* playerWithFile(const char * fileName);
    virtual void setPosition(const Point& pos);
    
};



#endif /* defined(SPRITE_PLATER) */
