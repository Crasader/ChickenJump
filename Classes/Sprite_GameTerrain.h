//
//  Sprite_Terrain.h
//  ChickenJump
//
//  Created by Asish Biswas on 26/05/15.
//
//

#ifndef SPRITE_GAMETERRAIN
#define SPRITE_GAMETERRAIN

#include <cocos2d.h>
#include "Sprite_Block.h"
#include "Sprite_Player.h"

#define TILE_H_SIZE 6
#define TILE_W_SIZE 8

using namespace cocos2d;

class GameTerrain : public Sprite {
public:
    // GameSprites 4 basic attributes
    CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(Point, _vector, Vector);
    
    CC_SYNTHESIZE(bool, _startTerrain, StartTerrain);
    
    GameTerrain(void);
    virtual ~GameTerrain(void);
    
    static GameTerrain * create();
    
    void checkCollision (Player * player);
    
    void move (float xMove);
    void reset (void);

private:
    Vector<Block *> _blockPool;
    int _blockPoolIndex;
    
    Vector<Block *> _blocks;
    int _lastBlockHeight;
    int _lastBlockWidth;
    int _minTerrainWidth;
    
    bool _showGap;
    Size _screenSize;
    
    int _currentPatternIndex;
    int _currentPatternCnt;
    int _currentWidthIndex;
    int _currentHeightIndex;
    int _currentTypeIndex;
    
    int _increaseGapInterval;
    float _increaseGapTimer;
    int _gapSize;
    
    // Private functions
    void initTerrain();
    void addBlocks(int currentWidth);
    void distributeBlocks();
    void initBlock(Block * block);
    
    inline float getWidth () {
        int width = 0;
        for (auto block : _blocks) {
            width += block->getWidth();
        }
        return width;
    }
};

#endif /* defined(SPRITE_GAMETERRAIN) */
