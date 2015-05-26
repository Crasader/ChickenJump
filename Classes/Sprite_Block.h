//
//  Sprite_Block.h
//  ChickenJump
//
//  Created by Asish Biswas on 25/05/15.
//
//

#ifndef SPRITE_BLOCK
#define SPRITE_BLOCK

#include <cocos2d.h>

using namespace cocos2d;

enum  {
    kBlockGap,
    kBlock1,
    kBlock2,
    kBlock3,
    kBlock4
    
};

class Block : public Sprite {
public:
    // GameSprites 4 basic attributes
    CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(Point, _vector, Vector);

    CC_SYNTHESIZE(int, _type, Type);
    
    Block(void);
    ~Block(void);
    
    static Block * create();
    void setupBlock(int width, int height, int type);
    
    inline virtual int left() {
        return this->getPositionX();
    }
    
    inline virtual int right() {
        return this->getPositionX() + _width;
    }
    
    inline virtual int top() {
        return this->getHeight();
    }
    
    inline virtual int bottom() {
        return 0;
    }

private:
    Size _screenSize;
    
    int _tileWidth;
    int _tileHeight;

};


#endif /* defined(SPRITE_BLOCK) */
