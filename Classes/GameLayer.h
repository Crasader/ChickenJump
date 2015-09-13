#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <cocos2d.h>

#include "Background.h"
#include "Chicken.h"
#include "LayerGround.h"
#include "LayerTwo.h"
#include "Trampoline.h"

using namespace cocos2d;

typedef enum {
    init,
    started,
    finishing,
    finished
    
} GameState;

class GameLayer : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    // contact listners
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    // touch listners
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    void update(float dt);
private:
    void addBG();
    void addChicken();
    void addContactListners();
    void addFirstLayer();
    void addGroundLayer();
    void addPauseMenu();
    void addSecondLayer();
    void addScoreLabel();
    void addTouchListners();
    void addTutorial();
    void endOfStage();
    void focusOnCharacter();
    void jump(float trampolinePositionY);
    void pause(cocos2d::Ref* sender);
    void releaseTouch();
    void removeEggSprite(Sprite* egg);
    inline void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _sceneWorld = world; }
    void spawnCloud(float dt);
    void spawnEgg();
    void spawnEndOfStageItem();
    void speedUp();
    void updateEggs(float speed);
    void updatePauseMenuPosition();
    void updateScoreLabel();
    void updateScoreLabelPosition();
    void updateStageComplesion(float speed);
    
    
    cocos2d::PhysicsWorld *_sceneWorld;
    
    Background* _background;
    LayerTwo* _layerTow;
    LayerGround* _layerGround;
    Chicken* _chicken;
    Trampoline* _trampoline;
    std::vector<Sprite*> _eggs;

    Sprite* _scoreIcon;
    Sprite* _finger;
    Sprite* _flag;
    Menu* _pauseMenu;
    Label* _scoreLabel;
    unsigned int _score;
    GameState _state;
    
    float _stageLength;
    float _elapsedStage;

    Vec2 _lineStartPoint;
    Vec2 _lineEndPoint;
    
    Vec2 _origin;
    Size _visibleSize;

};


//////////////////////////////////////////////////////////////////

class PauseLayer : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    void menuResumeCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseLayer);
};

#endif // __GAME_LAYER_H__







