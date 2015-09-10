#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <cocos2d.h>

#include "Background.h"
#include "Chicken.h"
#include "LayerGround.h"
#include "LayerTwo.h"
#include "Trampoline.h"

using namespace cocos2d;

class GameLayer : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    //listener for touches
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    void update(float dt);
    
private:
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _sceneWorld = world; }
    void spawnEgg(float dt);
    void spawnCloud(float dt);
    void speedUp(float dt);
    void updateEggs(float speed);
    void togglePause(cocos2d::Ref* layer);
    
    cocos2d::PhysicsWorld *_sceneWorld;
    Menu* _pauseToggleMenu;
    
    Background* _background;
    LayerTwo* _layerTow;
    LayerGround* _layerGround;
    Chicken* _chicken;
    Trampoline* _trampoline;
    std::vector<Sprite*> _eggs;
    Sprite* _finger;
    bool _isPaused;
    bool _isGameStarted;
    
    Vec2 _lineStartPoint;
    Vec2 _lineEndPoint;
    
    unsigned int _score;
    Label* _scoreLabel;
    Sprite* _scoreIcon;
    
    Vec2 _origin;
    Size _visibleSize;

};

#endif // __GAME_LAYER_H__
