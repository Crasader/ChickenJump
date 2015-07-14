#ifndef __GameLayer_SCENE_H__
#define __GameLayer_SCENE_H__

#include "cocos2d.h"
#include "Sprite_Player.h"
#include "Sprite_GameTerrain.h"

using namespace cocos2d;

typedef enum {
    kGameIntro,
    kGamePlay,
    kGameOver,
    kGameTutorial,
    kGameTutorialJump,
    kGameTutorialFloat,
    kGameTutorialDrop
    
} GameState;

class GameLayer : public cocos2d::Layer
{
public:
    virtual ~GameLayer();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    // Added Functions
    void update (float dt);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
private:
    GameTerrain * _terrain;
    Player * _player;
    
    Sprite * _intro;
    Sprite * _tryAgain;
    Sprite * _background;
    Sprite * _foreground;
    Sprite * _hat;
    Sprite * _jam;
    
    Action * _jamAnimate;
    Action * _jamMove;
    
    Vector<Sprite *> _clouds;
    
    SpriteBatchNode * _gameBatchNode;
    Label * _tutorialLabel;
    Menu* _mainMenu;
    
    Size _screenSize;
    
    GameState _state;
    
    Vec2 _lineStartPoint;
    Vec2 _lineEndPoint;
    
    bool _running;
    float _score;
    int _speedIncreaseInterval;
    float _speedIncreaseTimer;
    
    void createGameScreen();
    void resetGame();
};

#endif // __GameLayer_SCENE_H__
