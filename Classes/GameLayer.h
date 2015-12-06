#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <cocos2d.h>

#include "Background.h"
#include "Chicken.h"
#include "Collectable.h"
#include "LayerGround.h"
#include "LayerTwo.h"
#include "PauseLayer.h"
#include "ScoreLayer.h"
#include "SpecialCollectable.h"
#include "Trampoline.h"
#include "Stage.h"

using namespace cocos2d;

typedef enum {
    init,
    started,
    paused,
    finishing,
    finished
    
} GameState;

class GameLayer : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(Stage& stage);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    

    static GameLayer* getInstance();
    void pauseGame(cocos2d::Ref* sender);
    void resumeClicked(cocos2d::Ref* sender);
    void resumeGame(cocos2d::Ref* sender);
    
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
    void addExplosionEffect();
    void addFirstLayer();
    void addGroundLayer();
    void addPauseMenu();
    void addSecondLayer();
    void addTouchListners();
    void addTutorial();
    void cleanStage();
    void drawNewTrampoline();
    void endOfStage();
    void focusOnCharacter();
    void handleCollectableConsumption(Sprite* collectable);
    void initScoreHUDLives();
    void jump(float trampolinePositionY);
    void lastLifeExploded();
    void releaseTouch();
    void removeCollectable(Sprite* collectable);
    void removeSpecialCollectable(Sprite* collectable);
    void spawnCloud(float dt);
    void spawnCollectable();
    void spawnEndOfStageItem();
    void spawnSpecialObject();
    void speedUp();
    void updateCollectables(float speed);
    void updateSpecialCollectables(float speed);
    void updateScoreLabel();
    void updateStageComplesion(float speed);
    
    static GameLayer* _instance;
    
    Background* _background;
    LayerTwo* _layerTow;
    LayerGround* _layerGround;
    Chicken* _chicken;
    Trampoline* _trampoline;
    std::vector<Sprite*> _collectables;
    std::vector<Sprite*> _specialCollectables;
    GameState _state;
    Sequence* _sequence;

    PauseLayer* _pauseHUD;
    ScoreLayer* _scoreHUD;
    Sprite* _finger;
    Sprite* _flag;
    Menu* _pauseMenu;
    unsigned int _score;
    
    float _stageLength;
    float _stageRemaining;
    float _distanceForNewCollectables;
    float _distanceForNewSpecialObject;

    Vec2 _lineStartPoint;
    Vec2 _lineEndPoint;
    
    Vec2 _origin;
    Size _visibleSize;

};


#endif // __GAME_LAYER_H__







