#ifndef __GameLayer_SCENE_H__
#define __GameLayer_SCENE_H__

#include "cocos2d.h"
#include "Sprite_Player.h"
#include "Sprite_GameTerrain.h"

using namespace cocos2d;

enum {
    
    kBackground,
    kMiddleground,
    kForeground
};

class GameLayer : public cocos2d::Layer
{
public:
    virtual ~GameLayer();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    // Added Functions
    void update (float dt);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
private:
    GameTerrain * _terrain;
    Player * _player;
    
    SpriteBatchNode * _gameBatchNode;
    
    Size _screenSize;
    
    bool _running;
    int _speedIncreaseInterval;
    float _speedIncreaseTimer;
    
    void createGameScreen();
    void resetGame();
};

#endif // __GameLayer_SCENE_H__
