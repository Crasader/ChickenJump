//
//  Sprite_Block.h
//  ChickenJump
//
//  Created by Asish Biswas on 25/05/15.

//  When we instantiate a block in initBlock, we create a 5 x 4 building made out of wall tiles and roof tiles, each a sprite. And when we need to turn this building into a 3 x 2 building, or a 4 x 4 building, or whatever, we simply turn the excess tiles invisible at the end of setupBlock.

//  The texture used for the roof is picked randomly, but the one picked for the walls is based on building type (from our patterns array). It is also inside this for loop that all the tiles positioned at a point greater than the new building's width and height are turned invisible.
//
//

#ifndef SPRITE_BLOCK
#define SPRITE_BLOCK

#include <cocos2d.h>

using namespace cocos2d;

// GLOBAL ENUM {
enum {
    
    kBackground,
    kMiddleground,
    kForeground
};
enum {
    kSpritePlayer,
    kSpriteTerrain,
    kSpriteBlock,
    kSpriteChimney,
    kSpritePuff
};
// GLOBAL ENUM }

enum {
    kWallTile,
    kRoofTile,
    kChimney
};

enum {
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
    CC_SYNTHESIZE(Vector<Sprite*>, _chimneys, Chimneys);
//    CC_SYNTHESIZE_READONLY(bool, _puffing, Puffing);
    
    
    Block(void);
    virtual ~Block(void);
    
    static Block * create();
    void setupBlock(int width, int height, int type);
//    void setPuffing (bool value);
//    void hidePuffs();
    
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
    int _puffIndex;
    
    Vector<Sprite*> _wallTiles;
    Vector<Sprite*> _roofTiles;
    
    SpriteFrame * _tile1;
    SpriteFrame * _tile2;
    SpriteFrame * _tile3;
    SpriteFrame * _tile4;
    
    SpriteFrame * _roof1;
    SpriteFrame * _roof2;
    
//    Action * _puffAnimation;
//    Action * _puffSpawn;
//    Action * _puffMove;
//    Action * _puffFade;
//    Action * _puffScale;
    
    void initBlock();
//    void createPuff(void);

};


#endif /* defined(SPRITE_BLOCK) */
